#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

// Função para validar a conexão
int validate_connection(const char *url) {
    CURL *curl;
    CURLcode res;
    int success = 0;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            success = 1;
        } else {
            fprintf(stderr, "Falha na conexão: %s\n", curl_easy_strerror(res));
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return success;
}

// Função de força bruta
void brute_force(const char *target, int port, const char *username, const char *passwords[], int password_count) {
    char url[256];
    snprintf(url, sizeof(url), "http://%s:%d", target, port);

    for (int i = 0; i < password_count; ++i) {
        if (validate_connection(url)) {
            printf("Conectado ao %s com %s:%s\n", url, username, passwords[i]);
        } else {
            printf("Falha ao conectar com %s:%s\n", username, passwords[i]);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 5) {
        fprintf(stderr, "Uso: %s <target> <port> <username> <password1> <password2> ...\n", argv[0]);
        return 1;
    }
    //teste
    const char *target = argv[1];
    int port = atoi(argv[2]);
    const char *username = argv[3];
    const char **passwords = (const char **)&argv[4];
    int password_count = argc - 4;

    brute_force(target, port, username, passwords, password_count);

    return 0;
}
