


Patch to add command ```js_inline``` to nginx njs module.
To Apply this patch, run ```bash apply.sh /path/to/njs```
You can use ```js_inline``` in any place available for ```js_import```

Usage example:
-
```
js_inline test from '
    function ttt(){
        return "qqq";
    }
    export default {ttt};';
```

TODO: 
-
 - add removing temp files after nginx exits
