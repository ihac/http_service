all:
	gcc httpd.c myerr.c wrapper.c http_service.h -ggdb -o httpd
	gcc httpCli.c myerr.c wrapper.c http_service.h -ggdb -o httpCli
clean:
	rm httpd httpCli
