# TC275를 활용한 RC카 프로젝트
### 개발환경 : HighTec IDE

### 개발 process : V모델 기반 개발

### 개발 보드 : Infineon Technologies AURIX™ TC275 Lite 키트

## 1. 프로젝트명
- RC 카 제어

## 2. 프로젝트 배경 및 필요성
### 2.1 프로젝트 배경
- 키보드를 눌렀을 때 전진, 가속, 후진, 좌회전, 우회전, 감속, 정지 등의 실제 차량에서 볼법한 매끄러운 주행을 보여주도록 설계한다.
- 주행 외에도 초음파센서를 센싱하여 임의대로 설치해 둔 장애물에 근접시에 부저 경고음을 울리게 하거나 자율적으로 후방주차를 가능하게끔 한다.
- 블루투스를 통한 직접적인 조작외에도 초음파 센서의 거리 측정으로 차량이 자율적으로 주차공간에 후진하며 들어가 주차될 수 있도록 올바른 코드 로직을 구성한다.

### 2.2 프로젝트 목적
- 매트랩 시뮬링크를 활용한 MBD 코딩이 아닌 High Tec 툴을 활용한 핸드 코딩을 함으로써 단순히 추상화된 모델 개발이 아닌 하드웨어와 직접적으로 밀접한 코드를 짜는 연습을 한다.
- Uart0통신을 통해 블루투스에서 TC275에 입력을 넣고 Uart3통신을 통해 TC275에서 컴퓨터 내의 putty에 출력을 보내어 키보드의 입력값에 따라 코드들이 정상적으로 구현되게끔 한다.
- 차량의 바퀴 역할을 담당하는 모터의 정방향, 역방향에 따른 회전에 따라서 모형 차량의 주행 방향에 어떤 영향을 끼치는지 하드웨어적인 측면에서도 공부한다.

# 3. System_Architecture
<p align="center">
  <img src="/Architecture/System_Architecture.png" alt="HardWare_Architecture">
</p>

# 4. Hardware_Architecture
<p align="center">
  <img src="/Architecture/Hardware_Architecture.png" alt="HardWare_Architecture">
</p>

# 5. Software_Architecture_1
<p align="center">
  <img src="/Architecture/Software_Architecture_1.png" alt="HardWare_Architecture">
</p>

# 6. Software_Architecture_2
<p align="center">
  <img src="/Architecture/Software_Architecture_2.png" alt="HardWare_Architecture">
</p>

