설명서

0. 본 라이브러리는 minishell project를 위해 특별히 개조한 libft임 또한 모두 프로세스 종료시 ms_exit() 또는  중간에 기호에 따라 ms_clear_mem을 잘 호출한다는 가정 하에서 memory leak에서 자유로움

1. ms_lstnew를 포함한 모든 lst 함수 사용을 지양할 것

2. linked list와 같은 것이 필요한 경우 필히 ms_vector로 대체하여 사용할 것

3. ms_calloc은 alloced된 memory를 초기화 하지만, ms_malloc은 초기화하지 않으니, un-init value 를 조심할 것

4. libms의 모든 함수는 ms_exit()만 프로세스 종료 전에 호출해주면 동적 할당된 모든 메모리는 완벽하게 해제되니 ms_exit을 호출하는 것을 잊지 말 것, 그리고 절대 free()로 할당된 메모리로 해제시도하지 말 것, 그냥 모든 메모리를 해제 걱정말고 펑펑쓸것 만약 해제하게 되면 double free 오류가 날 수 있으니 절대 하지 말 것 - 어떻게 사용하는지 잘 이해가 가지 않는다면 unit_test.c를 컴파일해서 valgrind를 돌려볼 것

5. 만약 중간에 찜찜해서 해당 시점까지 동적 할당 된 메모리를 모두 해제하고 싶다면 ms_clear_mem을 호출해주면 모두 해제됨
free 대신 ms_clear_mem을 사용한다고 생각하면 편함 기호에 따라 사용할 것이며 필요 없다면 ms_exit에만 의존해도 무방함

6. 기존 libft에 없던 함수가 보인다면 libms.h에 있는 함수의 주석을 읽을 것

7. 마지막으로, malloc을 사용해야 할 때가 온다면 필히 standard lib의 malloc을 사용하지 말고 ms_malloc만을 사용할 것 그렇지 않다면, memory leak으로부터 safe함을 보장 불가능
