# 🎧 YouTube Audio Extractor (C)

Um programa simples em C para extrair o áudio de vídeos do YouTube e convertê-lo diretamente para os formatos **MP3** ou **WAV**, salvando automaticamente na sua pasta `Downloads`.

---

## ✅ Funcionalidades

- 🚀 Conversão direta de vídeos para MP3 ou WAV
- 🔍 Verificação automática de dependências (`yt-dlp` e `ffmpeg`)
- 🛠️ Instalação automática das dependências, se não estiverem presentes
- 🖥️ Totalmente operado via linha de comando
- 🗂️ Arquivos salvos automaticamente na pasta `~/Downloads`

---

## 🧰 Requisitos

- Sistema operacional baseado em Linux (testado no Ubuntu)
- Permissão para executar comandos com `sudo`
- Conexão com a internet

---

## 🛠️ Instalação

Clone o repositório e compile o programa com `gcc`:

```
git clone https://github.com/jonasnunees/extract-audio-youtube.git
cd youtube-audio-extractor-c
gcc -o extrator main.c
```
## 🚀 Como usar

### Sintaxe:

```
./extrator <URL do YouTube> <--mp3|--wav>
```

### Exemplos:

```
./extrator https://youtu.be/VIDEO_ID --mp3
./extrator https://www.youtube.com/watch?v=VIDEO_ID --wav
```

## 🆘 Ajuda

### Execute o comando com --help para ver a descrição completa:

```
./extrator --help
```

## 📂 Local onde os arquivos são salvos

### Todos os áudios convertidos são salvos automaticamente em:

```
~/Downloads
```

## 🔒 Permissões

#### Este programa pode pedir sua senha de sudo ao instalar yt-dlp ou ffmpeg, caso eles não estejam disponíveis no sistema.

## 🤝 Contribuições

#### Contribuições são bem-vindas! Se você tiver sugestões, correções ou quiser expandir o projeto, fique à vontade para abrir issues ou enviar pull requests.

## 📜 Licença

#### Este projeto é de código aberto, licenciado sob a GNU General Public License.

## 💡 Objetivo

#### Este programa foi desenvolvido com foco em acessibilidade e liberdade de uso. A ideia é permitir que qualquer pessoa — até mesmo iniciantes em programação — possam usar e entender como funciona por trás dos bastidores, incentivando o uso de software livre.
