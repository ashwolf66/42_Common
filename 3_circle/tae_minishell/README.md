# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    README.md                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: taejikim <taejikim@student.42gyeongsa      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/17 13:39:07 by taejikim          #+#    #+#              #
#    Updated: 2024/06/17 13:45:34 by taejikim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

[폴더 구성]

minishell
ㄴminishell_debug (디버깅 전용으로, 모든 tokenizing, parsing 과정이 print 됨)
ㄴminishell_release (디버깅 버전과 모든 것이 같지만, front_end 부분의 모든 print가 생략됨)

[공통]

minishell_*
ㄴ includes (minishell의 헤더와 libms의 헤더가 존재)
ㄴ lib (libms가 존재)
ㄴ srcs (minishell의 front_end 부분의 모든 코드가 존재)

val_check은 ./val_check으로 실행하며, readline의 mem leak과 error를 제외한 
minishell의 문제만을 보여줌 디버깅할 때 사용할 것

ignore_readline_leak.supp은 val_check에서 자체적으로 사용할 파일이며 설정파일에
불과하기에 직접 사용하지는 않을 것

makefile은 mandatory만을 컴파일하며 내부적으로 libms또한 컴파일 함 결과 바이너리 이름은
minishell임

* back_end 진행 중 minishell_debug 버전에서 파싱문제가 발견된다면 지체없이 통지부탁 *

[주요함수 설명]

ms_vector.c

벡터 자료형과 그 연산이 정의되어 있음

1. ms_vector_create(void)

vector 개체를 하나 malloc하여 리턴해줌

2. ms_vector_resize(t_vector *vector, size_t new_capacity)

vector 연산을 지원하는 helper함수이며 외부적으로 사용하지 않음

3. ms_vector_add(t_vector *vector, void *item)

create 된 vector 자료형에 요소를 맨 끝 배열에 추가하는 함수

4. ms_vector_remove(t_vector *vector, size_t index)

첫 번째 인자로 지정된 벡터 개체의 두 번째 인자로 받은 해당 index에 존재하는 요소를 삭제함

5. ms_vector_get(t_vector *vector, size_t index)

첫 번째 인자로 지정된 벡터 개체의 두 번째 인자로 받은 해당 index에 존재하는 요소의 주소를 리턴해줌

기타.c (libms 포함)

1, void	ms_exit(int status, char *msg, int out_chan);

첫 번째 인자로 exit code를, 필요하다면 두 번째 인자로 error message를, 필요없다면 NULL로 설정, 세번째로 출력 채널을 설정
결과적으로 주어진 값을 기반으로 exit()을 호출함

2. ms_malloc(size_t sz)

malloc과 같으나 malloc된 시작주소가 linked list에 쌓여 ms_exit, ms_clear_mem으로 일괄적 free가 가능하도록 지원해줌
해당 프로젝트에서는 표준 malloc보다 ms_malloc을 적극 권장, 사용할 것

3. ms_strlen_s(), ms_strjoin_s()

기본 libft의 기능과 같으나, 인자로 NULL이 들어와도 seg fault를 일으키지 않으며, strjoin은 한 쪽 이상이 NULL이더라도 strjoin이 가능함

4. ms_strndup()

표준 strndup과 같은 기능을 함

* 해당 프로젝트의 모든 함수는 ms_exit(), ms_clear_mem()을 명시적으로 프로세스 종료 전 호출해주기만 하면 일괄적으로 leak없이 free 되므로 free()의 명시적 호출 없이 마음 껏 사용할 것 *
* 주요함수 설명 section에서는, back end에서도 사용 될 함수의 설명에만 한정함 이외의 함수는 온전히 ms_front_end에서만 사용 *
