#!/bin/bash

set -e

#(cd $1 && git reset --hard || echo "Not a git repo")
sed -i -E "s/(\{.*ngx_string\(\"js_import\"\))/$(sed -z 's/\n/\\n/g' command.patch.c)\1/" $(grep 'ngx_string("js_import")' -rl $1)
sed -i -E "s/(.*ngx_command_t.+ngx)/$(sed -z 's/\n/\\n/g' proto.patch.c)\1/" $(grep 'ngx_string("js_import")' -rl $1)
find $(grep 'ngx_string("js_import")' -rl ../njs) -exec sh -c 'cat njs_inline.patch.c >> {}' \;
echo "Done"