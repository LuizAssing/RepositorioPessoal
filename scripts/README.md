# scripts/

Utilitários do repositório.

## gen_terminal_svg.py

Gera uma imagem SVG com aparência de terminal a partir de uma sessão de
texto real do programa. É assim que os `demo.svg` dos projetos em C foram
feitos.

As sessões ficam em [`sessions/`](sessions/). No arquivo de texto:

- `>>linha` — linha inteira em verde (comando digitado no shell)
- `texto<<valor` — o que vem depois de `<<` fica azul (valor digitado pelo usuário)

### Uso

```bash
python scripts/gen_terminal_svg.py scripts/sessions/quiz.txt projetos/quiz-vf-c/demo.svg
python scripts/gen_terminal_svg.py scripts/sessions/mercado.txt projetos/sistema-mercado-c/demo.svg
```
