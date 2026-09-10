#!/usr/bin/env python3
"""Gera um SVG estilo terminal a partir de uma sessao de texto real.

Marcadores no arquivo de entrada:
  >>texto   -> linha inteira em verde (comando digitado no shell)
  ...<<x    -> tudo depois de '<<' em azul (valor digitado pelo usuario)
"""
import html
import sys

BG = "#1a1a24"
BAR = "#2d2d3a"
FG = "#e4e4e7"
GREEN = "#7ee787"
BLUE = "#79c0ff"
DIM = "#8b949e"

CHAR_W = 8.4
LINE_H = 21
PAD_X = 24
BAR_H = 34
PAD_TOP = 26


def parse_line(line):
    """Retorna (comprimento, [(texto, cor), ...])."""
    if line.startswith(">>"):
        body = line[2:]
        return len(body), [(body, GREEN)]
    if "<<" in line:
        pre, typed = line.split("<<", 1)
        return len(pre) + len(typed), [(pre, FG), (typed, BLUE)]
    return len(line), [(line, FG)]


def render(raw, out):
    lines = [parse_line(l) for l in raw.rstrip("\n").split("\n")]
    width = max((n for n, _ in lines), default=40)
    width_px = int(PAD_X * 2 + width * CHAR_W)
    height_px = int(BAR_H + PAD_TOP + len(lines) * LINE_H + 18)

    parts = [
        f'<svg xmlns="http://www.w3.org/2000/svg" width="{width_px}" height="{height_px}" '
        f'viewBox="0 0 {width_px} {height_px}" '
        f'font-family="ui-monospace, SFMono-Regular, Consolas, monospace">',
        f'<rect width="{width_px}" height="{height_px}" rx="10" fill="{BG}"/>',
        f'<rect width="{width_px}" height="{BAR_H}" rx="10" fill="{BAR}"/>',
        f'<rect y="{BAR_H-10}" width="{width_px}" height="10" fill="{BAR}"/>',
        '<circle cx="20" cy="17" r="6" fill="#ff5f56"/>',
        '<circle cx="40" cy="17" r="6" fill="#ffbd2e"/>',
        '<circle cx="60" cy="17" r="6" fill="#27c93f"/>',
        f'<text x="{width_px/2}" y="21" fill="{DIM}" font-size="12" text-anchor="middle">bash</text>',
        '<text font-size="14" xml:space="preserve">',
    ]

    y = BAR_H + PAD_TOP
    for _, segs in lines:
        spans = []
        col = 0
        for text, color in segs:
            if text == "" and len(segs) == 1:
                text = " "
            x = PAD_X + col * CHAR_W
            spans.append(f'<tspan x="{x:.1f}" y="{y}" fill="{color}">{html.escape(text)}</tspan>')
            col += len(text)
        parts.append("".join(spans))
        y += LINE_H

    parts.append("</text></svg>")
    with open(out, "w", encoding="utf-8") as f:
        f.write("\n".join(parts) + "\n")
    print("ok:", out)


if __name__ == "__main__":
    src, dst = sys.argv[1], sys.argv[2]
    with open(src, encoding="utf-8") as f:
        render(f.read(), dst)
