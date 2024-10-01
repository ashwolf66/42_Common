#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test_tool/test_tool.c"

#include "../ex00/ft_strdup.c"
#include "../ex01/ft_range.c"
#include "../ex02/ft_ultimate_range.c"
#include "../ex03/ft_strjoin.c"
//#include "../ex04/ft_convert_base.c"
//#include "../ex04/ft_convert_base2.c"
//#include "../ex05/ft_split.c"

void ex00(int expect);
void ex01(int expect);
void ex02(int expect);
void ex03(int expect);
//void ex04(int expect);
//void ex05(int expect);
void print_arr(int *arr, int size);
void print_strs(char **strs);

int main(){
    print_answer(0, "ft_strdup.c", ex00);
    print_answer(1, "ft_range.c", ex01);
    print_answer(2, "ft_ultimate_range.c", ex02);
    print_answer(3, "ft_strjoin.c", ex03);
  //  print_answer(4, "ft_convert_base.c, ft_convert_base2", ex04);
    //print_answer(5, "ft_split.c", ex05);

    return 0;
}

void ex00(int expect)
{
    char *s1 = "";
    char *s2 = "asdfqwer";

    if(expect == COMMON_DESCRIPTION)
    {

    }
    else if(expect == RIGHT_ANSWER)
    {
        printf("\"%s\"(주소 : 임의의 주소 ) -> \"%s\"(주소 : 앞 주소와 다른 주소 )\n", s1, ft_strdup(s1));
        printf("\"%s\"(주소 : 임의의 주소 ) -> \"%s\"(주소 : 앞 주소와 다른 주소 )\n", s2, ft_strdup(s2));
    }
    else if (expect == USER_ANSWER)
    {
        printf("\"%s\"(주소 : %p ) -> \"%s\"(주소 : %p )\n", s1, s1, ft_strdup(s1), ft_strdup(s1));
        printf("\"%s\"(주소 : %p ) -> \"%s\"(주소 : %p )\n", s2, s2, ft_strdup(s2), ft_strdup(s2));
    }
}

void ex01(int expect)
{
    int min1 = -2;
    int max1 = 3;

    int min2 = 3;
    int max2 = 3;

    int min3 = 7;
    int max3 = 6;

    if(expect == COMMON_DESCRIPTION)
    {
        
    }
    else if(expect == RIGHT_ANSWER)
    {
        printf("\
min : -2, max : 3 -> \n\
-2 -1 0 1 2 \n\
\n\
min : 3, max : 3 -> \n\
반환된 포인터는 NULL입니다.\n\
\n\
min : 7, max : 6 ->\n\
반환된 포인터는 NULL입니다.\n\
        ");
    }
    else if(expect == USER_ANSWER)
    {
        printf("min : %d, max : %d -> \n", min1, max1);
        print_arr(ft_range(min1, max1), (max1 - min1));
        printf("\n");

        printf("min : %d, max : %d -> \n", min2, max2);
        print_arr(ft_range(min2, max2), (max2 - min2));
        printf("\n");

        printf("min : %d, max : %d -> \n", min3, max3);
        print_arr(ft_range(min3, max3), (max3 - min3));
        printf("\n");
    }
}

void ex02(int expect)
{
    int min1 = -2;
    int max1 = 3;

    int min2 = 3;
    int max2 = 3;

    int min3 = 7;
    int max3 = 6;

    int min4 = -2147483648;
    int max4 = 2147483647;

    int *arr1, *arr2, *arr3, *arr4;

    if(expect == COMMON_DESCRIPTION)
    {
        
    }
    else if(expect == RIGHT_ANSWER)
    {
        printf("\
min : -2, max : 3 -> return: 5\n\
-2 -1 0 1 2 \n\
\n\
min : 3, max : 3 -> return: 0\n\
반환된 포인터는 NULL입니다.\n\
\n\
min : 7, max : 6 -> return: 0\n\
반환된 포인터는 NULL입니다.\n\
\n\
min : -2147483648, max : 2147483647 -> return: -1\n\
반환된 포인터는 NULL입니다.\n\
        ");
    }
    else if(expect == USER_ANSWER)
    {
        printf("min : %d, max : %d -> return: %d\n", min1, max1, ft_ultimate_range(&arr1, min1, max1));
        print_arr(arr1, (max1 - min1));
        printf("\n");

        printf("min : %d, max : %d -> return: %d\n", min2, max2, ft_ultimate_range(&arr2, min2, max2));
        print_arr(arr2, (max2 - min2));
        printf("\n");

        printf("min : %d, max : %d -> return: %d\n", min3, max3, ft_ultimate_range(&arr3, min3, max3));
        print_arr(arr3, (max3 - min3));
        printf("\n");

        printf("min : %d, max : %d -> return: %d\n", min4, max4, ft_ultimate_range(&arr4, min4, max4));
        print_arr(arr4, (max4 - min4));
        printf("\n");
    }
}

void ex03(int expect)
{
    char *strs1[4];
    strs1[0] = "asdfqwer";
    strs1[1] = "ASDFQWER";
    strs1[2] = "zxcvasdf";
    strs1[3] = "fdsarewq";
    char *sep = ":;";

    if(expect == COMMON_DESCRIPTION)
    {
        printf("string 배열 : { ");
        for (int i = 0; i < 4; i++)
        {
            printf("%s", strs1[i]);
            if (i < 3)
                printf(", ");
            else
                printf(" }\n");
        }
        printf("sep : %s\n", sep);
    }
    else if(expect == RIGHT_ANSWER)
    {
        printf("\
size : 4\n\
 -> \"asdfqwer:;ASDFQWER:;zxcvasdf:;fdsarewq\"\n\
\n\
size : 0\n\
 -> \"\"\n\
\n\
size : 3\n\
 -> \"asdfqwer:;ASDFQWER:;zxcvasdf\"\n\
        ");
    }
    else if (expect == USER_ANSWER)
    {
        printf("size : %d\n -> \"%s\"\n\n", 4, ft_strjoin(4, strs1, sep));
        printf("size : %d\n -> \"%s\"\n\n", 0, ft_strjoin(0, strs1, sep));
        printf("size : %d\n -> \"%s\"\n\n", 3, ft_strjoin(3, strs1, sep));
    }
}
/*
void ex04(int expect)
{
    char *b0 = "0123456789";
    char *b1 = "asdfgqwert";
    char *b2 = "ui";
    char *b3 = "hjklyuio";
    char *b4 = "abcdefa";
    char *b5 = "a";
    char *b6 = "";

    char *nbr0 = "       ++--+--+-+-trewqgfds";
    char *nbr1 = "\v\t  ---trewqgfds-+a";

    if(expect == COMMON_DESCRIPTION)
    {

    }
    else if(expect == RIGHT_ANSWER)
    {
        printf("\
nbr : \"       ++--+--+-+-trewqgfds\", \n\
base_from : \"asdfgqwert\", \n\
base_to : \"0123456789\"\n\
 -> \"987654321\"\n\
\n\
\n\
nbr : \"       ++--+--+-+-trewqgfds\", \n\
base_from : \"asdfgqwert\", \n\
base_to : \"ui\"\n\
 -> \"iiiuiuiiuiiiiuuiiuiuuuiuiiuuui\"\n\
\n\
\n\
nbr : \"       ++--+--+-+-trewqgfds\", \n\
base_from : \"asdfgqwert\", \n\
base_to : \"hjklyuio\"\n\
 -> \"okioyiykij\"\n\
\n\
\n\
nbr : \"\n\
       	  ---trewqgfds-+a\", \n\
base_from : \"asdfgqwert\", \n\
base_to : \"hjklyuio\"\n\
 -> \"-okioyiykij\"\n\
\n\
\n\
nbr : \"       ++--+--+-+-trewqgfds\", \n\
base_from : \"asdfgqwert\", \n\
base_to : \"abcdefa\"\n\
 -> \"(null)\"\n\
\n\
\n\
nbr : \"       ++--+--+-+-trewqgfds\", \n\
base_from : \"a\", \n\
base_to : \"0123456789\"\n\
 -> \"(null)\"\n\
\n\
\n\
nbr : \"       ++--+--+-+-trewqgfds\", \n\
base_from : \"asdfgqwert\", \n\
base_to : \"\"\n\
 -> \"(null)\"\n\
        ");
    }
    else if (expect == USER_ANSWER)
    {
        printf("nbr : \"%s\", \nbase_from : \"%s\", \nbase_to : \"%s\"\n", nbr0, b1, b0);
        printf(" -> \"%s\"\n\n\n", ft_convert_base(nbr0, b1, b0));

        printf("nbr : \"%s\", \nbase_from : \"%s\", \nbase_to : \"%s\"\n", nbr0, b1, b2);
        printf(" -> \"%s\"\n\n\n", ft_convert_base(nbr0, b1, b2));

        printf("nbr : \"%s\", \nbase_from : \"%s\", \nbase_to : \"%s\"\n", nbr0, b1, b3);
        printf(" -> \"%s\"\n\n\n", ft_convert_base(nbr0, b1, b3));

        printf("nbr : \"%s\", \nbase_from : \"%s\", \nbase_to : \"%s\"\n", nbr1, b1, b3);
        printf(" -> \"%s\"\n\n\n", ft_convert_base(nbr1, b1, b3));

        printf("nbr : \"%s\", \nbase_from : \"%s\", \nbase_to : \"%s\"\n", nbr0, b1, b4);
        printf(" -> \"%s\"\n\n\n", ft_convert_base(nbr0, b1, b4));

        printf("nbr : \"%s\", \nbase_from : \"%s\", \nbase_to : \"%s\"\n", nbr0, b5, b0);
        printf(" -> \"%s\"\n\n\n", ft_convert_base(nbr0, b5, b0));

        printf("nbr : \"%s\", \nbase_from : \"%s\", \nbase_to : \"%s\"\n", nbr0, b1, b6);
        printf(" -> \"%s\"\n\n\n", ft_convert_base(nbr0, b1, b6));
    }
}

void ex05(int expect)
{
    char *str = "casd, fgcaw, ecat, gcdddcacaafd, cca";
    char *cs1, *cs2;

    cs1 = ", ";
    cs2 = "ca";

    if(expect == COMMON_DESCRIPTION)
    {

    }
    else if(expect == RIGHT_ANSWER)
    {
        printf("\
str : \"casd fgcaw, ecat gcdddcacaafd,cca\", \n\
charset : \", \"\n\
 -> \n\
\"casd\"\n\
\"fgcaw\"\n\
\"ecat\"\n\
\"gcdddcacaafd\"\n\
\"cca\"\n\
\n\
\n\
str : \"casd, fgcaw, ecat, gcdddcacaafd, cca\", \n\
charset : \"ca\"\n\
 -> \n\
\"sd, fg\"\n\
\"w, e\"\n\
\"t, g\"\n\
\"ddd\"\n\
\"fd, \"\n\
        ");
    }
    else if (expect == USER_ANSWER)
    {
        printf("str : \"%s\", \ncharset : \"%s\"\n -> \n", str, cs1);
        print_strs(ft_split(str, cs1));
        
        printf("str : \"%s\", \ncharset : \"%s\"\n -> \n", str, cs2);
        print_strs(ft_split(str, cs2));
    }
}
*/
void print_arr(int *arr, int size)
{
    if (!arr)
        printf("반환된 포인터는 NULL입니다.");
    for(int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void print_strs(char **strs)
{
    while(*strs){
        printf("\"%s\"\n", *(strs++));
    }
    printf("\n\n");
}
