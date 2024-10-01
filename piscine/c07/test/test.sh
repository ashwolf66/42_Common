echo "---------------------------------------------------"
printf "norminette -R checkForbiddenSourceHeader 실행 결과\n"
echo "---------------------------------------------------"
if norminette -R CheckForbiddenSourceHeader ../ex*/*.c
then
	printf "\n\n >> norminette 통과 \n\n";
	echo "---------------------------------------------------"
	printf "cc -Wall -Wextra -Werror 실행 결과\n"
	echo "---------------------------------------------------"
	if cc -Wall -Wextra -Werror -g c*_test.c -o test_tool/a.out
	then
		printf "\n\n >> 컴파일 성공\n\n";
		if ./test_tool/a.out
		then	
			rm test_tool/a.out;
		else
			printf "\n\n >> 프로그램 비정상 종료됨.\n\n";
			rm test_tool/a.out;
		fi
	else
		printf "\n\n >> 컴파일 실패. 에러 발생\n\n";
	fi
else
	printf "\n\n >> norminette 통과 실패\n\n";
fi
echo "---------------------------------------------------"

