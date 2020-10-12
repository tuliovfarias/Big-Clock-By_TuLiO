git filter-branch --tree-filter '
if [ -d "Projeto-BigClock/test3" ]; then
  mv "Projeto-BigClock/test3" "Projeto-BigClock/test4"
fi' --force HEAD