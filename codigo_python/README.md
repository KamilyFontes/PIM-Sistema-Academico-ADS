
---

# Código em Python — Interface Gráfica (Tkinter)

Esta pasta contém o código em **Python** responsável pela **visualização dos dados** gerados pelo sistema em C.  
O programa lê os arquivos `alunos.txt` e `notas.txt`, exibe as informações em uma tabela interativa e calcula automaticamente a **média final** e a **situação** dos alunos.

---

## Funcionalidades

- Leitura automática dos arquivos `alunos.txt` e `notas.txt`;
- Exibição dos dados em uma interface gráfica (Tkinter);
- Cálculo da média ponderada:
  \[
  \text{Média} = \frac{(NP1 \times 4) + (NP2 \times 4) + (PIM \times 2)}{10}
  \]
- Exibição da **situação do aluno**:
  - Aprovado (média ≥ 5)
  - Reprovado (média < 5)
- Botão de **atualização de dados** em tempo real.

---

## Estrutura dos Arquivos

📁 codigo-python/
├── interface_alunos.py → código principal em Python
├── alunos.txt → arquivo gerado pelo programa em C
└── notas.txt → arquivo com notas lançadas




