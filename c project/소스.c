#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> // Sleep �Լ� ���

// �ζ� ��ȣ�� ������ ���� ����
#define LOTTO_MAX 45
#define LOTTO_COUNT 6

// ȭ�� �ʱ�ȭ
void clear_screen() {
    system("cls");
}

// ���� �ζ� ��ȣ ���� �Լ�
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

// ���� ���� �Լ� (���� ����)
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

// �ִϸ��̼� ȿ�� ���
void display_animation(int* numbers) {
    char display[LOTTO_COUNT][10]; // ȭ�鿡 ��µ� �� ���� ����
    for (int i = 0; i < LOTTO_COUNT; i++) {
        snprintf(display[i], sizeof(display[i]), "( 0 )"); // �ʱ� ����
    }

    for (int i = 0; i < LOTTO_COUNT; i++) {
        // ( �� )�� �ٲٱ�
        snprintf(display[i], sizeof(display[i]), "( �� )");
        for (int j = 0; j < LOTTO_COUNT; j++) {
            printf("%s ", display[j]);
        }
        printf("\r"); // Ŀ���� �� ������ �̵�
        fflush(stdout);
        Sleep(200); // 0.2�� ���

        // Ȯ���� ��ȣ�� �ٲٱ�
        snprintf(display[i], sizeof(display[i]), "( %2d )", numbers[i]);
        for (int j = 0; j < LOTTO_COUNT; j++) {
            printf("%s ", display[j]);
        }
        printf("\r");
        fflush(stdout);
        Sleep(200); // 0.2�� ���
    }
}

// Ư�� ��ȣ ���� �ζ� ��ȣ ����
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

// Ư�� ��ȣ ���� �ζ� ��ȣ ����
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

// ���� �Լ�
int main() {
    while (1) {
        int choice;
        int lotto_numbers[LOTTO_COUNT];
        int included[LOTTO_COUNT], excluded[LOTTO_COUNT];

        srand((unsigned int)time(NULL));

        printf("\n=== �ζ� ��÷ ���α׷� ===\n");
        printf("1. �ζ� ��ȣ �ڵ� ����\n");
        printf("2. Ư�� ��ȣ ���� �� ����\n");
        printf("3. Ư�� ��ȣ ���� �� ����\n");
        printf("4. �ζ� ������Ʈ�� �̵�\n");
        printf("5. ����\n");
        printf("����: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1: {
            printf("�� ���� �ζ� ��ȣ�� �����Ͻðڽ��ϱ�? ");
            int lines;
            scanf_s("%d", &lines);
            for (int i = 0; i < lines; i++) {
                generate_lotto_numbers(lotto_numbers);
                sort_numbers(lotto_numbers, LOTTO_COUNT);
                display_animation(lotto_numbers);
                printf("\n�ζ� ��ȣ %d: ", i + 1);
                for (int j = 0; j < LOTTO_COUNT; j++) {
                    printf("%d ", lotto_numbers[j]);
                }
                printf("\n");
            }
            break;
        }
        case 2: {
            printf("�� ���� ��ȣ�� �����ұ��? ");
            int include_count;
            scanf_s("%d", &include_count);
            printf("������ ��ȣ�� �Է��ϼ���: ");
            for (int i = 0; i < include_count; i++) {
                scanf_s("%d", &included[i]);
            }
            printf("�� ���� �ζ� ��ȣ�� �����Ͻðڽ��ϱ�? ");
            int lines;
            scanf_s("%d", &lines);
            for (int i = 0; i < lines; i++) {
                include_lotto_numbers(included, include_count, lotto_numbers);
                sort_numbers(lotto_numbers, LOTTO_COUNT);
                display_animation(lotto_numbers);
                printf("\n������ �ζ� ��ȣ %d: ", i + 1);
                for (int j = 0; j < LOTTO_COUNT; j++) {
                    printf("%d ", lotto_numbers[j]);
                }
                printf("\n");
            }
            break;
        }
        case 3: {
            printf("�� ���� ��ȣ�� �����ұ��? ");
            int exclude_count;
            scanf_s("%d", &exclude_count);
            printf("������ ��ȣ�� �Է��ϼ���: ");
            for (int i = 0; i < exclude_count; i++) {
                scanf_s("%d", &excluded[i]);
            }
            printf("�� ���� �ζ� ��ȣ�� �����Ͻðڽ��ϱ�? ");
            int lines;
            scanf_s("%d", &lines);
            for (int i = 0; i < lines; i++) {
                exclude_lotto_numbers(excluded, exclude_count, lotto_numbers);
                sort_numbers(lotto_numbers, LOTTO_COUNT);
                display_animation(lotto_numbers);
                printf("\n������ �ζ� ��ȣ %d: ", i + 1);
                for (int j = 0; j < LOTTO_COUNT; j++) {
                    printf("%d ", lotto_numbers[j]);
                }
                printf("\n");
            }
            break;
        }
        case 4:
            printf("�ζ� ������Ʈ�� �̵��մϴ�...\n");
            system("start https://www.dhlottery.co.kr/common.do?method=main");
            break;
        case 5:
            printf("���α׷��� �����մϴ�.\n");
            return 0;
        default:
            printf("�߸��� �����Դϴ�.\n");
        }

        printf("\n�ƹ� Ű�� ������ ȭ���� �������� ���α׷��� ����۵˴ϴ�...\n");
        getchar(); 
        getchar(); 
        clear_screen();
    }
    return 0;
}
