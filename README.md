qimhangul-qt5
=============

## 소개
qimhangul-qt5는 Qt 5를 위한 한글 입력 모듈입니다. Qt 5의 입력기 지원 방식은 Qt
4와 비교하였을 때 다음과 같은 차이가 있습니다:

* xim 지원 중단.
* 입력기 플러그인을 만들 때 필요한 클래스가 QInputContext에서
  QPlatformInputContext로 변경됨. QPlatformInputContext는 QPA (Qt Platform
Abstraction)의 일부로 제공되기 때문에 더 이상 공식적인 클래스로 지원되지 않음.

qimhangul-qt5는 [qimhangul](https://github.com/choehwanjin/qimhangul)의 코드를
기반으로 합니다.

## 빌드 및 설치
빌드하기 위해서는 libhangul 패키지 0.0.4 버전 이상이 필요합니다.
libhangul은 다음 링크에서 구하실 수 있습니다.
http://kldp.net/projects/hangul/

## 빌드와 설치 방법

    $ mkdir build
    $ cd build
    $ qmake ../
    $ make
    # sudo make install


## 설정 방법
Qt 4와 Qt 5가 공존하는 환경이라면 환경 변수 QT4_IM_MODULE 및 QT_IM_MODULE이 각각
Qt 4와 5의 입력기 설정을 담당합니다. 만약 현재 사용 중인 환경에서 환경 변수가
위와 다르다면 알맞게 조정하십시오.

만약 Qt 5의 입력기 환경 변수가 QT_IM_MODULE이라면 아래와 같이 설정할 수
있습니다.

* QT_IM_MODULE=hangul:2 - 두벌식
* QT_IM_MODULE=hangul:3f - 세벌식 최종
* QT_IM_MODULE=hangul:39 - 세벌식 최종

이 외 libhangul에서 사용하는 자판을 사용하려면 hangul: 다음 libhangul 소스의
hangul/hangulinputcontext.c의 HangulKeyboard 구조체의 두 번째 인자를 지정하면
됩니다.

## 사용 방법
한영 전환키는 Shift+Space, Hangul키 입니다.
한자 변환키는 F9, Hangul_Hanja 키 입니다.
