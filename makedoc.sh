#!/bin/bash

# 시스템에 맞게 한글 폰트 이름 설정 (아래 중 하나 선택)
MAIN_FONT="Apple SD Gothic Neo"       # macOS
# MAIN_FONT="NanumGothic"             # Ubuntu
# MAIN_FONT="Malgun Gothic"           # Windows

for mdfile in *.md; do
  base="${mdfile%.md}"

  echo "변환 시작: $mdfile"

  # DOCX 변환
  pandoc "$mdfile" -o "${base}.docx" --toc
  echo "  DOCX 변환 완료: ${base}.docx"

  # PDF 변환 (폰트 지정, 아이콘 지원 없음)
  pandoc "$mdfile" -o "${base}.pdf" --toc \
    --pdf-engine=xelatex \
    -V mainfont="$MAIN_FONT"

  if [ $? -eq 0 ]; then
    echo "  PDF 변환 완료: ${base}.pdf"
  else
    echo "  ⚠ PDF 변환 실패: ${base}.pdf (폰트 설치 또는 이름 확인 필요)"
  fi

  echo "변환 완료: $mdfile"
  echo "------------------------------"
done
