# Программируемая игровая платформа

## Цель
Написать программируемую игровую платформу, основанную на алгоритме ментальный покер

## Задачи
* Спроектировать структуру и логику приложения
* Разработать и реализовать сетевой протокол
* Используя Pawn Abstract Machine (for the Pawn language) Copyright (c) ITB CompuPhase разработать игровой процесс
* Реализовать большую арифметику для RSA и ментального покера
* Связать всю логику в одну библиотеку
* Сделать интерфейс с подключением библиотеки

## Скриншоты
![Переписка](https://sun9-27.userapi.com/impg/MwVgPRcEOyRwrYS6AcuHkQNZAxUSTRSqW8PW5w/2v3_ztSi2LA.jpg?size=944x665&quality=96&sign=3d7bca1adadfcf3a36368b73cc176681&type=album)

## Компиляция
Скачайте библиотеху amx с сайта [https://www.compuphase.com/pawn/pawn.htm](https://www.compuphase.com/pawn/pawn.htm)
Разместите ее по адресу Diploma/core/GameProcess/amx, внеся изменения в соответствии с файлом Diploma/README.txt
Запустите скрипт Diploma/core/makecore
Затем откройте в QtCreator Visual/Diploma/Diploma.pro и скомпилируйте проект

## Cтруктура проекта
```markdown
.
├── Diploma
│   ├── compile
│   ├── core
│   │   ├── apilist.hpp
│   │   ├── Asker
│   │   │   ├── serverchannel.cpp
│   │   │   ├── serverchannel.hpp
│   │   │   ├── serverproto.cpp
│   │   │   └── serverproto.hpp
│   │   ├── BigInt
│   │   │   ├── armtest.cpp
│   │   │   ├── autotest.cpp
│   │   │   ├── biginteger.cpp
│   │   │   ├── biginteger.hpp
│   │   │   ├── criptotest.cpp
│   │   │   ├── makefile
│   │   │   ├── setCapVersion
│   │   │   ├── setLastVersion
│   │   │   └── UtilVersion
│   │   │       ├── 1_1
│   │   │       │   ├── biginteger.cpp
│   │   │       │   └── biginteger.hpp
│   │   │       └── Cap
│   │   │           ├── biginteger.cpp
│   │   │           └── biginteger.hpp
│   │   ├── core.cpp
│   │   ├── core.hpp
│   │   ├── coreinterface.cpp
│   │   ├── coreinterface.hpp
│   │   ├── GameProcess
│   │   │   ├── datamanipulator.cpp
│   │   │   ├── datamanipulator.hpp
│   │   │   ├── forpawn.cpp
│   │   │   ├── forpawn.hpp
│   │   │   ├── gameclasses
│   │   │   │   ├── card.cpp
│   │   │   │   ├── card.hpp
│   │   │   │   ├── desk.cpp
│   │   │   │   ├── desk.hpp
│   │   │   │   ├── game.cpp
│   │   │   │   ├── game.hpp
│   │   │   │   ├── group.cpp
│   │   │   │   ├── group.hpp
│   │   │   │   ├── player.cpp
│   │   │   │   └── player.hpp
│   │   │   ├── gameproc.cpp
│   │   │   ├── gameproc.hpp
│   │   │   ├── mentalpoker.cpp
│   │   │   ├── mentalpoker.hpp
│   │   │   ├── scriptapi.cpp
│   │   │   ├── scriptapi.hpp
│   │   │   └── tmp
│   │   │       ├── forpawn (copy).cpp
│   │   │       └── forpawn (copy).hpp
│   │   ├── libcore.hpp
│   │   ├── makecore
│   │   └── NetProto
│   │       ├── clientchannel.cpp
│   │       ├── clientchannel.hpp
│   │       ├── clientproto.cpp
│   │       ├── clientproto.hpp
│   │       ├── commands.h
│   │       ├── globalsocket.cpp
│   │       └── globalsocket.hpp
│   ├── makeserver
│   ├── maketestmode
│   ├── modes
│   │   ├── modelist
│   │   └── test.pwn
│   ├── testclient.cpp
│   └── testserver.cpp
├── README.md
└── Visual
    ├── build-Diploma-Desktop_Qt_5_6_0_GCC_64bit-Debug
    │   ├── cards
    │   │   ├── 10clubs.png
    │   │   ├── 10diamonds.png
    │   │   ├── 10hearts.png
    │   │   ├── 10spades.png
    │   │   ├── 2clubs.png
    │   │   ├── 2diamonds.png
    │   │   ├── 2hearts.png
    │   │   ├── 2spades.png
    │   │   ├── 3clubs.png
    │   │   ├── 3diamonds.png
    │   │   ├── 3hearts.png
    │   │   ├── 3spades.png
    │   │   ├── 4clubs.png
    │   │   ├── 4diamonds.png
    │   │   ├── 4hearts.png
    │   │   ├── 4spades.png
    │   │   ├── 5clubs.png
    │   │   ├── 5diamonds.png
    │   │   ├── 5hearts.png
    │   │   ├── 5spades.png
    │   │   ├── 6clubs.png
    │   │   ├── 6diamonds.png
    │   │   ├── 6hearts.png
    │   │   ├── 6spades.png
    │   │   ├── 7clubs.png
    │   │   ├── 7diamonds.png
    │   │   ├── 7hearts.png
    │   │   ├── 7spades.png
    │   │   ├── 8clubs.png
    │   │   ├── 8diamonds.png
    │   │   ├── 8hearts.png
    │   │   ├── 8spades.png
    │   │   ├── 9clubs.png
    │   │   ├── 9diamonds.png
    │   │   ├── 9hearts.png
    │   │   ├── 9spades.png
    │   │   ├── Aclubs.png
    │   │   ├── Adiamonds.png
    │   │   ├── Ahearts.png
    │   │   ├── Aspades.png
    │   │   ├── back.png
    │   │   ├── BlackJoker.png
    │   │   ├── Jclubs.png
    │   │   ├── Jdiamonds.png
    │   │   ├── Jhearts.png
    │   │   ├── Jspades.png
    │   │   ├── Kclubs.png
    │   │   ├── Kdiamonds.png
    │   │   ├── Khearts.png
    │   │   ├── Kspades.png
    │   │   ├── Qclubs.png
    │   │   ├── Qdiamonds.png
    │   │   ├── Qhearts.png
    │   │   ├── Qspades.png
    │   │   └── RedJoker.png
    │   ├── lib
    │   ├── Makefile
    │   ├── moc_dialogaddparam.cpp
    │   ├── moc_dialogclaim.cpp
    │   ├── moc_dialogcreategame.cpp
    │   ├── moc_dialogdownload.cpp
    │   ├── moc_dialoggame.cpp
    │   ├── moc_dialogjoin.cpp
    │   ├── moc_dialoglogenter.cpp
    │   ├── moc_dialogreg.cpp
    │   ├── moc_mainwindow.cpp
    │   ├── moc_qcards.cpp
    │   ├── modes
    │   │   └── modelist
    │   ├── ui_dialogaddparam.h
    │   ├── ui_dialogclaim.h
    │   ├── ui_dialogcreategame.h
    │   ├── ui_dialogdownload.h
    │   ├── ui_dialoggame.h
    │   ├── ui_dialogjoin.h
    │   ├── ui_dialoglogenter.h
    │   ├── ui_dialogreg.h
    │   └── ui_mainwindow.h
    └── Diploma
        ├── CoreInterface
        │   ├── apilist.hpp
        │   └── coreinterface.hpp
        ├── desktop.ini
        ├── dialogaddparam.cpp
        ├── dialogaddparam.h
        ├── dialogaddparam.ui
        ├── dialogclaim.cpp
        ├── dialogclaim.h
        ├── dialogclaim.ui
        ├── dialogcreategame.cpp
        ├── dialogcreategame.h
        ├── dialogcreategame.ui
        ├── dialoggame.cpp
        ├── dialoggame.h
        ├── dialoggame.ui
        ├── dialogjoin.cpp
        ├── dialogjoin.h
        ├── dialogjoin.ui
        ├── dialoglogenter.cpp
        ├── dialoglogenter.h
        ├── dialoglogenter.ui
        ├── dialogreg.cpp
        ├── dialogreg.h
        ├── dialogreg.ui
        ├── Diploma.pro
        ├── Diploma.pro.user
        ├── Diploma.pro.user.2.3pre1
        ├── Diploma.pro.user.2.5pre1
        ├── main.cpp
        ├── mainwindow.cpp
        ├── mainwindow.h
        ├── mainwindow.ui
        ├── QCards
        │   ├── qcards.cpp
        │   └── qcards.hpp
        └── utils
            ├── apilist.hpp
            └── corezombie.hpp
```

