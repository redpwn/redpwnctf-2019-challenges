; Use https://github.com/Storyyeller/Krakatau to assemble into classfile
;
; J5 - Allows JSR + no stackframes
.version 49 0

; Class name
.class public JavaIsEZ

; Extends java/lang/Object
.super java/lang/Object

; Predicate to create complex ctl flow in decompilers
.field private static synthetic a I

; flag = "flag{j4v4_1s_4s_h4rd_4s-n4t1v3_sQ4aaHZ3of}" (42 chars)

.method public static main : ([Ljava/lang/String;)V 
    .code stack 10 locals 14
LbogusJump3:
    goto L0
Lwrong:
LbogusJump2:
    ldc 'noob'
    jsr Lprint
    return
Lcorrect:
    pop
LbogusJump:
    ldc 'You got it right :P'
    jsr Lprint
    return
Lassign_arr:
    astore 11
    aload 8
    swap
    iload 7
    swap
    iastore
    iinc 7 1
    ret 11
Linit_key_arr:
    astore_1
    iconst_0
    istore 7
    bipush 8
    newarray int
    astore 8
    bipush 97
    jsr Lassign_arr
    bipush 71
    jsr Lassign_arr
    bipush 94
    jsr Lassign_arr
    bipush 89
    jsr Lassign_arr
    bipush 90
    jsr Lassign_arr
    bipush 121
    jsr Lassign_arr
    bipush 72
    jsr Lassign_arr
    bipush 53
    jsr Lassign_arr
    ret 1
Lset_len:
    astore_1
    iconst_0
    istore 5
Llen_one:
    iload 5
    iload_2
    isub
    ifne Llen_two
    ret 1
Llen_two:
    iinc 5 1
    aload 4
    monitorenter
    goto Llen_one
Lprint:
    pop
    getstatic java/lang/System out Ljava/io/PrintStream;
    swap
    invokevirtual java/io/PrintStream println (Ljava/lang/Object;)V
    return
L0:
    aconst_null
    checkcast 'redpwnCTF_says_stop_using_ur_decompiler'
    ldc 'java.utils.ArrayList'
    invokestatic java/lang/Class forName (Ljava/lang/String;)Ljava/lang/Class;
    invokestatic java/util/concurrent/ThreadLocalRandom current ()Ljava/util/concurrent/ThreadLocalRandom;
    iconst_1
    ldc 65535
    invokevirtual java/util/concurrent/ThreadLocalRandom nextInt (II)I
    putstatic JavaIsEZ a I
    pop2
    aconst_null
    goto L2
L1:
    .catch [0] from L0 to L1 using L2
    .catch [0] from L3 to L4 using L2
    .catch [0] from L20 to L21 using L2
L3:
    aload_0
    aconst_null
    astore_0
    monitorexit
L4:
    goto L0
L20:
    aconst_null
    athrow
L21:
    goto L0
L2:
    getstatic JavaIsEZ a I
    istore 13
    iconst_0
    istore_2
    iconst_0
    istore_3
    ifnull L0
    iload 13
    lookupswitch
        1 : LbogusJump
        -555 : LbogusJump2
        4882 : LbogusJump3
        default : Lnext
Lnext:
    aload_0
    arraylength
    iconst_1
    isub
    ifge L5
    ldc 'You need to specify the flag...'
    jsr Lprint
L5:
    aload_0
    iconst_0
    aaload
    astore_3
    aload_3
    invokevirtual java/lang/String length ()I
    bipush 42
    isub
    ifeq L6
    ldc 'noob'
    jsr Lprint
    return
L6:
    aload_3
    invokevirtual java/lang/String toCharArray ()[C
    astore 4
    aload 4
    arraylength
    istore_2
    new java/lang/Object
    dup
    invokespecial java/lang/Object <init> ()V
    astore 6
    jsr Lset_len
    jsr Linit_key_arr
    iconst_0
    istore 9
    new java/lang/StringBuilder
    dup
    invokespecial java/lang/StringBuilder <init> ()V
    astore 12
    aconst_null
L7:
    iload 9
    ifeq L9
    pop
    aload 12
    invokevirtual java/lang/StringBuilder toString ()Ljava/lang/String;
    ldc '\x07\x2b\x3f\x3e\x21\x13\x7c\x43\x55\x18\x6f\x2a\x05\x4d\x3b\x6a\x09\x73\x2c\x3d\x05\x4d\x3b\x18\x0f\x73\x2a\x68\x2c\x4a\x17\x46\x30\x73\x3f\x38\x12\x23\x7b\x5a\x07\x3a'
    invokevirtual java/lang/String equals (Ljava/lang/Object;)Z
    ifne Lwin
    goto Lwrong
Lwin:
    jsr Lcorrect
L9:
    pop
    invokestatic java/util/concurrent/ThreadLocalRandom current ()Ljava/util/concurrent/ThreadLocalRandom;
    iconst_1
    ldc 65535
    invokevirtual java/util/concurrent/ThreadLocalRandom nextInt (II)I
    istore 9
    iconst_0
    istore 10
    ; Loop
Lloop:
    aload 4
    monitorexit
    aload 12
    aload 4
    iload 10
    caload
    aload 8
    dup
    iload 10
    swap
    arraylength
    irem
    iaload
    ixor
    i2c
    invokevirtual java/lang/StringBuilder append (C)Ljava/lang/StringBuilder;
    pop
    iinc 10 1
    ; End of loop

    iconst_0
    istore 9
    iload 13
    ifne L0
    goto Lloop
L8:
    .catch java/lang/IllegalMonitorStateException from L7 to L8 using L7
    return
    .end code
.end method 
.end class 
