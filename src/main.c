#include <stdio.h>      // Para entrada e saída (printf, etc.)
#include <stdlib.h>     // Para funções utilitárias (system, etc.)
#include <string.h>     // Para manipulação de strings (strcmp, strstr, etc.)
#include <unistd.h>     // Para funções do sistema (acesso a comandos, etc.)
#include <sys/stat.h>   // Para verificar arquivos/diretórios no sistema

// Define o tamanho máximo para comandos do terminal
#define MAX_CMD 1024

// Define o diretório onde os arquivos serão salvos
#define DOWNLOAD_DIR "~/Downloads"

// Função que verifica se um comando (ex: yt-dlp, ffmpeg) existe no sistema
int comando_existe(const char *comando) {
    char cmd[MAX_CMD];
    // Monta um comando do shell que checa se o comando existe (usando `command -v`)
    snprintf(cmd, sizeof(cmd), "command -v %s > /dev/null 2>&1", comando);
    // Executa o comando e retorna 1 se existir, 0 se não
    return system(cmd) == 0;
}

// Função que instala o ffmpeg automaticamente via apt
int instalar_ffmpeg() {
    printf("Instalando ffmpeg...\n");
    // Atualiza o repositório e instala o ffmpeg
    return system("sudo apt update && sudo apt install -y ffmpeg") == 0;
}

// Função que instala o yt-dlp diretamente do GitHub (última versão)
int instalar_yt_dlp_manual() {
    printf("Instalando yt-dlp (versão mais recente)...\n");
    // Baixa o executável yt-dlp para /usr/local/bin
    int res = system("sudo curl -L https://github.com/yt-dlp/yt-dlp/releases/latest/download/yt-dlp -o /usr/local/bin/yt-dlp");
    if (res != 0) return 0;
    // Dá permissão de execução para o binário
    return system("sudo chmod a+rx /usr/local/bin/yt-dlp") == 0;
}

// Função que verifica se a URL informada parece ser válida do YouTube
int url_valida(const char *url) {
    // Retorna verdadeiro se a URL contém "youtube.com/watch" ou "youtu.be/"
    return strstr(url, "youtube.com/watch") || strstr(url, "youtu.be/");
}

// Função que exibe a ajuda do programa (--help)
void exibir_ajuda(const char *nome_programa) {
    printf("\n");
    printf("Uso:\n");
    printf("  %s <URL do YouTube> <--mp3|--wav>\n", nome_programa);
    printf("\n");
    printf("Descrição:\n");
    printf("  Este programa extrai e converte o áudio de vídeos do YouTube diretamente\n");
    printf("  para o formato MP3 ou WAV, salvando o resultado na pasta Downloads.\n");
    printf("\n");
    printf("Opções:\n");
    printf("  --mp3      Converte o áudio para o formato MP3\n");
    printf("  --wav      Converte o áudio para o formato WAV\n");
    printf("  --help     Exibe esta mensagem de ajuda\n");
    printf("\n");
    printf("Exemplos:\n");
    printf("  %s https://youtu.be/VIDEO_ID --mp3\n", nome_programa);
    printf("  %s https://youtube.com/watch?v=VIDEO_ID --wav\n", nome_programa);
    printf("\n");
}

// Função principal do programa
int main(int argc, char *argv[]) {
    // Se o usuário passar apenas --help, exibe a ajuda e encerra
    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        exibir_ajuda(argv[0]);
        return 0;
    }

    // Verifica se o número de argumentos está correto (espera 3)
    if (argc != 3) {
        printf("Erro: número de argumentos inválido.\n");
        printf("Use '%s --help' para mais informações.\n", argv[0]);
        return 1;
    }

    // Pega a URL e o formato de áudio desejado (passados como argumento)
    const char *url = argv[1];
    const char *formato = argv[2];

    // Verifica se a URL parece ser válida
    if (!url_valida(url)) {
        printf("Erro: URL inválida. Use um link do YouTube.\n");
        return 1;
    }

    // Verifica se o yt-dlp está instalado. Se não estiver, instala.
    if (!comando_existe("yt-dlp")) {
        if (!instalar_yt_dlp_manual()) {
            printf("Erro ao instalar yt-dlp. Encerrando.\n");
            return 1;
        }
    }

    // Verifica se o ffmpeg está instalado. Se não estiver, instala.
    if (!comando_existe("ffmpeg")) {
        if (!instalar_ffmpeg()) {
            printf("Erro ao instalar ffmpeg. Encerrando.\n");
            return 1;
        }
    }

    // Define a variável onde o comando final será montado
    char comando[MAX_CMD];

    // Monta o comando do terminal para extrair o áudio em MP3
    if (strcmp(formato, "--mp3") == 0) {
        snprintf(comando, sizeof(comando),
                 "yt-dlp -x --audio-format mp3 -P %s \"%s\"", DOWNLOAD_DIR, url);
    }
    
    // Monta o comando para extrair o áudio em WAV
    else if (strcmp(formato, "--wav") == 0) {
        snprintf(comando, sizeof(comando),
                 "yt-dlp -x --audio-format wav -P %s \"%s\"", DOWNLOAD_DIR, url);
    }
    
    // Se o usuário passou uma opção inválida de formato
    else {
        printf("Formato inválido. Use --mp3 ou --wav\n");
        return 1;
    }

    // Exibe que a conversão está começando
    printf("Extraindo e convertendo o áudio...\n");

    // Executa o comando que faz o download e conversão do áudio
    int resultado = system(comando);

    // Verifica se deu tudo certo
    if (resultado == 0) {
        printf("✅ Conversão concluída com sucesso! Arquivo salvo em %s\n", DOWNLOAD_DIR);
    } else {
        printf("❌ Falha na conversão do áudio.\n");
    }

    // Finaliza o programa
    return 0;
}
