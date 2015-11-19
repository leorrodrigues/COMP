.class public entradaJasmin
.super java/lang/Object

.method public <init>()V
   aload_0

   invokenonvirtual java/lang/Object/<init>()V
   return
.end method

.method public static main([Ljava/lang/String;)V
   .limit stack 2
   .limit locals 11
   iconst_1
   istore 1
   iconst_2
   iload 1
   iadd
   istore 2
   iconst_2
   istore 3
   iload 3
   ldc 1000
   imul
   istore 3
   iload 1
   iload 2
   iadd
   istore 5
   iload 5
   iconst_2
   idiv
   istore 6
   iload 5
   iload 6
   iadd
   istore 4
   getstatic java/lang/System/out Ljava/io/PrintStream;
   iload 1
   invokevirtual java/io/PrintStream/println(I)V
   getstatic java/lang/System/out Ljava/io/PrintStream;
   iload 2
   invokevirtual java/io/PrintStream/println(I)V
   getstatic java/lang/System/out Ljava/io/PrintStream;
   iload 3
   invokevirtual java/io/PrintStream/println(I)V
   getstatic java/lang/System/out Ljava/io/PrintStream;
   iload 4
   invokevirtual java/io/PrintStream/println(I)V
   getstatic java/lang/System/out Ljava/io/PrintStream;
   iload 5
   invokevirtual java/io/PrintStream/println(I)V
   getstatic java/lang/System/out Ljava/io/PrintStream;
   iload 6
   invokevirtual java/io/PrintStream/println(I)V
   return
.end method
