char *ngx_js_inline(ngx_conf_t *cf, ngx_command_t *cmd, void *conf){
    void *out;
    char tmp[200] = {0};
    ngx_str_t  *value=cf->args->elts;
    int from = (cf->args->nelts == 4);

    if (!from) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "js_inline should be NAME from CODE");
        return NGX_CONF_ERROR;
    }else{
        if (ngx_strcmp(value[2].data, "from") != 0) {
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "js_inline invalid parameter \"%V\"", &value[2]);
            return NGX_CONF_ERROR;
        }
    }
    if (!tmpnam(tmp)){
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "js_inline could not get name of temp file");
        return NGX_CONF_ERROR;
    }
    if (!tmp[0]){
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "js_inline could not create temp file");
        return NGX_CONF_ERROR;
    }
    int fd = open(tmp, O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (fd<0){
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "js_inline could not create temp file");
        return NGX_CONF_ERROR;
    }
    if (write(fd, value[3].data, value[3].len)<0){
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "js_inline could not fill temp file");
        return NGX_CONF_ERROR;
    }
    close(fd);
    if (value[3].len < strlen(tmp)){
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "js_inline error, please increase size of inline code string (TODO: need to fix)");
        return NGX_CONF_ERROR;
    }

    memcpy(value[3].data, tmp, strlen(tmp));
    value[3].len=strlen(tmp);
    out = ngx_js_import(cf, cmd, conf);
//    remove(tmp);
    return out;
}
