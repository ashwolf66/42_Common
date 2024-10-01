#include <stdio.h>

typedef void (*expect_func_t) (int);

enum TypeOfPrint{
    USER_ANSWER,
    RIGHT_ANSWER,
    COMMON_DESCRIPTION
};

void print_answer(int ex_num, char *file_name, expect_func_t exp_func)
{
    printf("\n\n========================================\n");
    printf("  ex%02d   ||   ", ex_num);
    printf("%s\n\n", file_name);
    exp_func(COMMON_DESCRIPTION);
    printf("\n\n 정답 \n");
    exp_func(RIGHT_ANSWER);
    printf("\n>>\n\n 내 실행 결과\n");
    exp_func(USER_ANSWER);
}