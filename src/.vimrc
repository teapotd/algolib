"!!CONVERT-BREAKS
se ai cin cul ic is nu scs sw=4 ts=4 so=7 ttm=9
sy on
vn _ :w !cpp -dD -P -fpreprocessed \| \
		sed -z sg\\sggg \| md5sum \| cut -c-4 <cr>
