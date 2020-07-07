extern int add_vals (int a, int b, int c);

#define PI 3.14159		//variable
#define ADD(a,b) (a+b)	//function
#define MY_TEXT "This is some text to replace.\n"	//use of text


/*"extern" tells the compiler that this function is to ve found 
 *externally to the file, i.e. in another c file*/

/*using #define saves memory due to preprocessor complile vs use of 
 * floating point variable*/

/*If you use #define for text strings, they should be enclosed in 
 * double quotes, otherwise the replaced text will end at the first 
 * space. So use #define MY_TEXT "This is some text to replace." 
 * The double quotes are included in the replacement, so you can then 
 * just call printf(MY_TEXT);*/
