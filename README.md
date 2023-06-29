# mini-machine-search

## Convenções de desenvolivmento
- Código em português
- Commits em português

## IMPLEMENTAÇÕES
- [x] S : red black tree com chave id e valor a palavra
- [x] struct documento
- [x] struct's red black tree
- [x] calcular page rank
- [x] T : red black tree com chave palavra e valor vetor de documentos (ordenados por PR)
- [ ] ir lendo e processando linha por linha da entrada padrão
- [ ] fazer lógica de busca dos termos

## BUGS
- [ ] falta um free (alocado em "linkaDocumentos")
  - Ele da erro nos casos exemplos 1 e 2, mas no 0 não

## MELHORIAS
- [x] O vetor page rank está estático. Fazer dinâmico? (acho que não precisa)
- [ ] RBT genérica