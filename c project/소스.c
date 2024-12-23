#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> // Sleep 함수 사용

// 로또 번호의 범위와 개수 정의
#define LOTTO_MAX 45
#define LOTTO_COUNT 6

// 화면 초기화
void clear_screen() {
    system("cls");
}

// 랜덤 로또 번호 생성 함수
void generate_lotto_numbers(int* lotto_numbers) {
    int count = 0;
    while (count < LOTTO_COUNT) {
        int num = rand() % LOTTO_MAX + 1;
        int duplicate = 0;
        for (int i = 0; i < count; i++) {
            if (lotto_numbers[i] == num) {
                duplicate = 1;
                break;
            }
        }
        if (!duplicate) {
            lotto_numbers[count++] = num;
        }
    }
}

// 숫자 정렬 함수 (버블 정렬)
void sort_numbers(int* numbers, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (numbers[j] > numbers[j + 1]) {
                int temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }
}

// 애니메이션 효과 출력
void display_animation(int* numbers) {
    char display[LOTTO_COUNT][10]; // 화면에 출력될 공 상태 저장
    for (int i = 0; i < LOTTO_COUNT; i++) {
        snprintf(display[i], sizeof(display[i]), "( 0 )"); // 초기 상태
    }

    for (int i = 0; i < LOTTO_COUNT; i++) {
        // ( ● )로 바꾸기
        snprintf(display[i], sizeof(display[i]), "( ● )");
        for (int j = 0; j < LOTTO_COUNT; j++) {
            printf("%s ", display[j]);
        }
        printf("\r"); // 커서를 맨 앞으로 이동
        fflush(stdout);
        Sleep(200); // 0.2초 대기

        // 확정된 번호로 바꾸기
        snprintf(display[i], sizeof(display[i]), "( %2d )", numbers[i]);
        for (int j = 0; j < LOTTO_COUNT; j++) {
            printf("%s ", display[j]);
        }
        printf("\r");
        fflush(stdout);
        Sleep(200); // 0.2초 대기
    }
}

// 특정 번호 포함 로또 번호 생성
void include_lotto_numbers(int* included, int included_count, int* lotto_numbers) {
    int count = 0;
    for (int i = 0; i < included_count; i++) {
        lotto_numbers[count++] = included[i];
    }
    while (count < LOTTO_COUNT) {
        int num = rand() % LOTTO_MAX + 1;
        int duplicate = 0;
        for (int i = 0; i < count; i++) {
            if (lotto_numbers[i] == num) {
                duplicate = 1;
                break;
            }
        }
        if (!duplicate) {
            lotto_numbers[count++] = num;
        }
    }
}

// 특정 번호 제외 로또 번호 생성
void exclude_lotto_numbers(int* excluded, int excluded_count, int* lotto_numbers) {
    int count = 0;
    while (count < LOTTO_COUNT) {
        int num = rand() % LOTTO_MAX + 1;
        int exclude = 0;
        for (int i = 0; i < excluded_count; i++) {
            if (excluded[i] == num) {
                exclude = 1;
                break;
            }
        }
        if (!exclude) {
            int duplicate = 0;
            for (int i = 0; i < count; i++) {
                if (lotto_numbers[i] == num) {
                    duplicate = 1;
                    break;
                }
            }
            if (!duplicate) {
                lotto_numbers[count++] = num;
            }
        }
    }
}

// 메인 함수
int main() {
    while (1) {
        int choice;
        int lotto_numbers[LOTTO_COUNT];
        int included[LOTTO_COUNT], excluded[LOTTO_COUNT];

        srand((unsigned int)time(NULL));

        printf("\n=== 로또 추첨 프로그램 ===\n");
        printf("1. 로또 번호 자동 생성\n");
        printf("2. 특정 번호 포함 후 생성\n");
        printf("3. 특정 번호 제외 후 생성\n");
        printf("4. 로또 웹사이트로 이동\n");
        printf("5. 종료\n");
        printf("선택: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1: {
            printf("몇 줄의 로또 번호를 생성하시겠습니까? ");
            int lines;
            scanf_s("%d", &lines);
            for (int i = 0; i < lines; i++) {
                generate_lotto_numbers(lotto_numbers);
                sort_numbers(lotto_numbers, LOTTO_COUNT);
                display_animation(lotto_numbers);
                printf("\n로또 번호 %d: ", i + 1);
                for (int j = 0; j < LOTTO_COUNT; j++) {
                    printf("%d ", lotto_numbers[j]);
                }
                printf("\n");
            }
            break;
        }
        case 2: {
            printf("몇 개의 번호를 포함할까요? ");
            int include_count;
            scanf_s("%d", &include_count);
            printf("포함할 번호를 입력하세요: ");
            for (int i = 0; i < include_count; i++) {
                scanf_s("%d", &included[i]);
            }
            printf("몇 줄의 로또 번호를 생성하시겠습니까? ");
            int lines;
            scanf_s("%d", &lines);
            for (int i = 0; i < lines; i++) {
                include_lotto_numbers(included, include_count, lotto_numbers);
                sort_numbers(lotto_numbers, LOTTO_COUNT);
                display_animation(lotto_numbers);
                printf("\n생성된 로또 번호 %d: ", i + 1);
                for (int j = 0; j < LOTTO_COUNT; j++) {
                    printf("%d ", lotto_numbers[j]);
                }
                printf("\n");
            }
            break;
        }
        case 3: {
            printf("몇 개의 번호를 제외할까요? ");
            int exclude_count;
            scanf_s("%d", &exclude_count);
            printf("제외할 번호를 입력하세요: ");
            for (int i = 0; i < exclude_count; i++) {
                scanf_s("%d", &excluded[i]);
            }
            printf("몇 줄의 로또 번호를 생성하시겠습니까? ");
            int lines;
            scanf_s("%d", &lines);
            for (int i = 0; i < lines; i++) {
                exclude_lotto_numbers(excluded, exclude_count, lotto_numbers);
                sort_numbers(lotto_numbers, LOTTO_COUNT);
                display_animation(lotto_numbers);
                printf("\n생성된 로또 번호 %d: ", i + 1);
                for (int j = 0; j < LOTTO_COUNT; j++) {
                    printf("%d ", lotto_numbers[j]);
                }
                printf("\n");
            }
            break;
        }
        case 4:
            printf("로또 웹사이트로 이동합니다...\n");
            system("start https://www.dhlottery.co.kr/common.do?method=main");
            break;
        case 5:
            printf("프로그램을 종료합니다.\n");
            return 0;
        default:
            printf("잘못된 선택입니다.\n");
        }

        printf("\n아무 키나 누르면 화면이 지워지고 프로그램이 재시작됩니다...\n");
        getchar(); 
        getchar(); 
        clear_screen();
    }
    return 0;
}
