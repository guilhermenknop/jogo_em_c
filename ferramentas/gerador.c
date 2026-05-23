#include <stdio.h>

void gerarCenario(int altura, int largura) {
    printf("char cenario[%d][%d] = {\n", altura, largura);

    for (int y = 0; y < altura; y++) {
        printf("    {");

        for (int x = 0; x < largura; x++) {
            char c;

            // Bordas
            if (y == 0 || y == altura - 1 || x == 0 || x == largura - 1) {
                c = '#';
            } else {
                c = ' ';
            }

            printf("'%c'", c);

            if (x < largura - 1) {
                printf(",");
            }
        }

        printf("}");

        if (y < altura - 1) {
            printf(",");
        }

        printf("\n\n");
    }

    printf("};\n");
}

int main() {
    int altura, largura;

    //printf("Altura: ");
    scanf("%d", &altura);

    //printf("Largura: ");
    scanf("%d", &largura);

    gerarCenario(altura, largura);

    return 0;
}