::simplelife_nick@hotmail.com
:: 批量将本目录中的所有.C .h .cpp文件用Astyle进行代码美化操作
::2014年10月6日
::设置Astyle命令位置和参数
::(1) -f
::在两行不相关的代码之间插入空行，如import和public class之间、public class和成员之间等；
::(2) -p
::在操作符两边插入空格，如=、+、-等。
::如：int a=10*60;
::处理后变成int a = 10 * 60;
::(3) -P
::在括号两边插入空格。另，-d只在括号外面插入空格，-D只在里面插入。
::如：MessageBox.Show ("aaa");
::处理后变成MessageBox.Show ( "aaa" );
::(4) -U
::移除括号两边不必要的空格。
::如：MessageBox.Show ( "aaa" );
::处理后变成MessageBox.Show ("aaa");
::(5) -V
::将Tab替换为空格。
::--style=ansi：ANSI 风格格式和缩进
::
::namespace foospace
::{
::　int Foo()
::　{
::　　if (isBar)
::　　{
::　　　bar();
::　　　return 1;
::　　}
::　　else
::　　　return 0;
::　}
::}

::--style=kr ：Kernighan&Ritchie 风格格式和缩进

::namespace foospace {
::　int Foo() {
::　　if (isBar) {
::　　　bar();
::　　　return 1;
::　　} else
::　　　return 0;
::　}
::}

::--style=linux ：Linux 风格格式和缩进

::namespace foospace
::{
::　int Foo()
::　{
::　　if (isBar) {
::　　　bar();
::　　　return 1;
::　　} else 
::　　　return 0;
::　}
::}

::--style=gnu ：GNU 风格格式和缩进

::namespace foospace
::{
::　int Foo()
::　{
::　　if (isBar)
::　　{
::　　　bar();
::　　　return 1;
::　　}
::　　else
::　　　return 0;
::　}
::}
::
::--style=java ：Java 风格格式和缩进
::class foospace {
::　int Foo() {
::　　if (isBar) {
::　　　bar();
::　　　return 1;
::　　} else
::　　　return 0;
::　}
::}

@echo off
::下面请设置astyle的绝对路径
set astyle="D:\Application\AStyle\bin\astyle.exe"

::循环遍历目录
for /r . %%f in (*.cpp;*.c;*.h;) do %astyle% --style=ansi -p -P -n "%%f"
exit