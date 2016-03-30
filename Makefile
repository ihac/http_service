all:
	gcc httpd.c myerr.c wrapper.c http_service.h -ggdb -o httpd
	gcc httpd_v2.c myerr.c wrapper.c http_service.h -ggdb -o httpd2
	gcc httpCli.c myerr.c wrapper.c http_service.h -ggdb -o httpCli
clean:
	rm httpd httpCli
