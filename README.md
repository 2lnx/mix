# mix wav sound

	这是一次尝试

##Using dependent
	> using boost::filesystem
	> using std

##Flatform
	> Windows x86 and x64

##提高性能
	> 使用Windows API CreateThread引入多线程结构，对待mix音轨分片，并使用多线程方式同时Mix两条音轨。
	> 使用API WaitForMultipleObjects处理多线程Mix结果的同步问题。避免多音轨处理时污染数据。
	> 

#Contact
> ---