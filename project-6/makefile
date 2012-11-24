all: threads

threads: parta partb partc partd 

parta:
	gcc parta.c -o parta -lpthread
partb:
	gcc partb.c -o partb -lpthread
partc:
	gcc partc.c -o partc -lpthread
partd:
	gcc partd.c -o partd -lpthread

run: clean

clean:
	rm -f *o threads 
