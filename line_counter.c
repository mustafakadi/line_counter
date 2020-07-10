#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>


#define PRINT_NUM(token) printf(#token " is |%d|\n", token)
#define PRINT_STR(token, order) printf(#token " -%d- is |%s|\n", order, token)

unsigned long int processed_dir_cnt;
unsigned long int processed_file_cnt;

unsigned long int cpp_file_cnt;
unsigned long int hpp_file_cnt;
unsigned long int c_file_cnt;
unsigned long int h_file_cnt;
unsigned long int dat_file_cnt;
unsigned long int gpj_file_cnt;


unsigned long int total_line_cnt;
unsigned long int cpp_line_cnt;
unsigned long int hpp_line_cnt;
unsigned long int c_line_cnt;
unsigned long int h_line_cnt;
unsigned long int dat_line_cnt;
unsigned long int gpj_line_cnt;

unsigned char log_enabled;

FILE *log_file;


/*
 * Date............: 12-Dec-2018 18:06
 * Function........: is_dir
 * .................
 */
unsigned char is_dir(unsigned char *name)
{
DIR *tmp_dir;


tmp_dir = opendir(name);
if (tmp_dir != NULL)
 {
	closedir(tmp_dir);
	return (1);
 }
else	return (0);
}


/*
 * Date............: 12-Dec-2018 18:06
 * Function........: is_search_str_only
 * .................
 */
unsigned char is_search_str_only(unsigned char *name, unsigned char str_length)
{
unsigned char tmp_length = 0;
unsigned char *tmp_ptr;


if (name == 0)
	return 0;

tmp_ptr = name;

while (*tmp_ptr != '\0')
 {
	tmp_length++;

	if (tmp_length > str_length)
		return 0;

	tmp_ptr++;
 }

return 1;
}


/*
 * Date............: 12-Dec-2018 18:30
 * Function........: recursive_file_iteration
 * .................
 */
void recursive_file_iteration(unsigned char *dir_path_str)
{
DIR			*curr_dir;
FILE			*curr_file;
struct dirent		*dir_content;
unsigned char		curr_dir_str[250];
unsigned char		curr_line[1000];
unsigned char		*exist_cpp_ptr = 0, *exist_hpp_ptr = 0, *exist_c_ptr = 0, *exist_h_ptr = 0, *exist_dat_ptr = 0, *exist_gpj_ptr = 0;
unsigned char		*exist_ghs_ptr = 0, *exist_vscode_ptr = 0;


if (is_dir(dir_path_str))
 {
	curr_dir = opendir(dir_path_str);

	fprintf(log_file, "%s\n", dir_path_str);
	
	processed_dir_cnt++;
 }
else	return;

if (curr_dir == NULL)
	return;

while ((dir_content = readdir(curr_dir)) != NULL)
 {
	if ( (strcmp(dir_content -> d_name, ".") == 0) || (strcmp(dir_content -> d_name, "..") == 0) ) 
		continue;

	strcpy(curr_dir_str, dir_path_str);
	strcat(curr_dir_str, "/");
	strcat(curr_dir_str, dir_content -> d_name);

	if (is_dir(curr_dir_str))
	 {
		exist_ghs_ptr = strstr(dir_content -> d_name, "ghs");
		exist_vscode_ptr = strstr(dir_content -> d_name, "vscode");

		if (exist_ghs_ptr || exist_vscode_ptr)
			continue;
		else	recursive_file_iteration(&curr_dir_str[0]);

		continue;
	 }

	exist_cpp_ptr = strstr(dir_content -> d_name, ".cpp");
	if (is_search_str_only(exist_cpp_ptr, 4) == 0)
		exist_cpp_ptr = 0;

	exist_hpp_ptr = strstr(dir_content -> d_name, ".hpp");
	if (is_search_str_only(exist_hpp_ptr, 4) == 0)
		exist_hpp_ptr = 0;

	exist_c_ptr = strstr(dir_content -> d_name, ".c");
	if (is_search_str_only(exist_c_ptr, 2) == 0)
		exist_c_ptr = 0;

	exist_h_ptr = strstr(dir_content -> d_name, ".h");
	if (is_search_str_only(exist_h_ptr, 2) == 0)
		exist_h_ptr = 0;

	exist_dat_ptr = strstr(dir_content -> d_name, ".dat");
	if (is_search_str_only(exist_dat_ptr, 4) == 0)
		exist_dat_ptr = 0;

	exist_gpj_ptr = strstr(dir_content -> d_name, ".gpj");
	if (is_search_str_only(exist_gpj_ptr, 4) == 0)
		exist_gpj_ptr = 0;

	if (exist_cpp_ptr || exist_hpp_ptr || exist_c_ptr || exist_h_ptr || exist_dat_ptr || exist_gpj_ptr)
	 {
		curr_file = fopen(curr_dir_str, "r");
		
		if (curr_file == NULL) continue;

		processed_file_cnt++;

		fprintf(log_file, "\t%s\n", dir_content -> d_name);

		if (exist_cpp_ptr)
			cpp_file_cnt++;
		else if (exist_hpp_ptr)
			hpp_file_cnt++;
		else if (exist_c_ptr)
			c_file_cnt++;
		else if (exist_h_ptr)
			h_file_cnt++;
		else if (exist_dat_ptr)
			dat_file_cnt++;
		else if (exist_gpj_ptr)
			gpj_file_cnt++;

		while (fgets(curr_line, sizeof(curr_line), curr_file))
		 {
			total_line_cnt++;

			if (exist_cpp_ptr)
				cpp_line_cnt++;
			else if (exist_hpp_ptr)
				hpp_line_cnt++;
			else if (exist_c_ptr)
				c_line_cnt++;
			else if (exist_h_ptr)
				h_line_cnt++;
			else if (exist_dat_ptr)
				dat_line_cnt++;
			else if (exist_gpj_ptr)
				gpj_line_cnt++;
		 }

		fclose(curr_file);
	 }
 }

closedir(curr_dir);
}


/*
 * Date............: 12-Dec-2018 18:06
 * Function........: main
 * .................
 */
int main(int argc, char *argv[])
{

log_file = fopen("line_counter_log.txt", "w");

processed_dir_cnt = 0;
processed_file_cnt = 0;

cpp_file_cnt = 0;
hpp_file_cnt = 0;
c_file_cnt = 0;
h_file_cnt = 0;
dat_file_cnt = 0;
gpj_file_cnt = 0;

total_line_cnt = 0;
cpp_line_cnt = 0;
hpp_line_cnt = 0;
c_line_cnt = 0;
h_line_cnt = 0;
dat_line_cnt = 0;
gpj_line_cnt = 0;

recursive_file_iteration("/users/u3/vobs/ddx6/ddx6");
//recursive_file_iteration("/users/u7/mkadiog/fun/dir_iter/test_vob");

printf("\n**Configuration Results**\n-------------------------\n");
printf("Processed Directory Count:\t\t\t%lu\n", processed_dir_cnt);

printf("\nProcessed Total File Count:\t\t\t%lu\n", processed_file_cnt);
printf("\tProcessed \".cpp\" File Count:\t\t%lu\n", cpp_file_cnt);
printf("\tProcessed \".hpp\" File Count:\t\t%lu\n", hpp_file_cnt);
printf("\tProcessed \".c\" File Count:\t\t%lu\n", c_file_cnt);
printf("\tProcessed \".h\" File Count:\t\t%lu\n", h_file_cnt);
printf("\tProcessed \".dat\" File Count:\t\t%lu\n", dat_file_cnt);
printf("\tProcessed \".gpj\" File Count:\t\t%lu\n", gpj_file_cnt);

printf("\n*Total Line Count:\t\t\t\t*%lu*\n", total_line_cnt);
printf("\tTotal Line Count in \".cpp\" Files:\t%lu\n", cpp_line_cnt);
printf("\tTotal Line Count in \".hpp\" Files:\t%lu\n", hpp_line_cnt);
printf("\tTotal Line Count in \".c\" Files:\t\t%lu\n", c_line_cnt);
printf("\tTotal Line Count in \".h\" Files:\t\t%lu\n", h_line_cnt);
printf("\tTotal Line Count in \".dat\" Files:\t%lu\n", dat_line_cnt);
printf("\tTotal Line Count in \".gpj\" Files:\t%lu\n", gpj_line_cnt);

fclose(log_file);

return (1);
}
