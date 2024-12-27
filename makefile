compile:
	gcc -o prog *.c -lncurses && clear && echo "Executable mis à jour avec succès"

run:
	clear && ./prog

clean:
	rm -f prog highscoresBE.txt && clear && echo "Executable et meilleurs scores supprimés avec succès"