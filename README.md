# Linux-MyShell-Project

<br>

### - 작품설명 -

<br>

본 프로젝트는 우분투를 이용한 리눅스 환경에서 기존에 제공하는 Shell의 기능을 코드로 구현해 진행해봤던 프로젝트입니다. cat, cd, cp, pwd, ln, mkdir, stat, ls, chmod, exit와 같은 총 9가지 기능을 구현하는 데 성공했고 앞으로 history, alias, [n]-history, ps 기능은 이후에 추가적으로 구현할 계획이다.
<br><br>

  
### -목차-

1. [cat](#cat)<br>
2. [cd](#cd)<br>
3. [cp](#cp)<br>
4. [pwd](#pwd)<br>
5. [ln](#ln)<br>
6. [rm](#rn)<br>
7. [mkdir](#mkdir)<br>
8. [stat](#stat)<br>
9. [ls](#ls)<br>
10. [chmod](#chmod)<br>
11. [eixt](#exit)<br>

<hr>

<br><br>
우선 테스트 시작에 앞서 테스트에 사용하기 위해서 asdf라는 내용과 이름을 가지는 파일과 qwer이라는 이름을 가진 디렉토리를 하나씩 만들겠습니다.
<br><br>

## cat<br><br>
cat은 cat 명령 뒤에 파일 이름을 입력하면 그 파일의 내용을 출력하는 코드입니다.
보통 cat filename 이러한 형식으로 많이 사용됩니다.
<br><br>

테스트 결과 :

![slide1](https://user-images.githubusercontent.com/74617086/182412212-33e042d1-38ef-4ec4-a2c9-10a1332cfefa.JPG)

<br><br>

## cd<br><br>
cd는 현재 작업중인 작업 디렉토리의 위치를 바꾸는 명령어입니다. 보통 cd [dir_name] 이나 cd 단독으로 사용됩니다.
<br><br>
테스트 결과:

<br><br>

## cp<br><br>
cp는 파일을 복사하는 명령어입니다. 보통 cp [복사할 파일] [붙여 넣기할 파일]의 형태로 사용됩니다.
<br><br>
테스트 결과:

<br><br>

## pwd<br><br>
pwd는 현재 작업이 진행되고 있는 파일의 디렉토리 경로를 출력하는 명령어입니다. 보통 pwd 단독으로 사용됩니다.
<br><br>
테스트 결과 :
<br><br>

## rm<br><br>
rm은 파일을 삭제하는 명령어입니다. 보통 rm [삭제할 파일]의 형태로 많이 사용됩니다.
<br><br>
테스트 결과:
<br><br>


## rm<br><br>
ln은 지정한 파일의 링크 파일을 만드는 명령어입니다. 프로젝트에선 하드 링크를 구현했으며 ln [원본 파일] [링크 파일]과 같은 형태로 구현했습니다.
<br><br>
테스트 결과:
<br><br>

## mkdir<br><br>
mkdir은 디렉터리를 생성하는 명령어입니다. 보통 mkdir [dir_name]의 형식으로 사용됩니다.
<br><br>
테스트 결과:
<br><br>

## stat<br><br>
stat은 티렉토리나 파일의 다양한 정보를 확인할 수 있는 명령어입니다. stat [파일,디렉토리]와 같은 형태로 사용되며 ls와 다르게 요약되지 않은 정보를 출력합니다.
<br><br>
테스트 결과:
<br><br>

## ls<br><br>
ls는 작업 중인 디렉터리에 있는 디렉터리와 파일 등을 확인해 출력하는 명령어입니다. 보통 ls, ls –al의 형식으로 사용됩니다,
<br><br>
테스트 결과:
<br><br>

## chmod<br><br>
chmod는 파일의 권한을 변경해주는 명령어입니다. chmod [바꾸고자 하는 권한] [파일이름]의 형태로 많이 사용됩니다.
<br><br>
테스트 결과:

<br><br>
## exit<br><br>
exit은 쉘이나 스크립트에서 사용되는 종료 명령어입니다. 보통 exit 단일로 사용됩니다.
<br><br>
테스트 결과:

