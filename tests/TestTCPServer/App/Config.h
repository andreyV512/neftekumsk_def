#pragma once
#pragma message("����������� ���� ����������!!!")
//undef DEBUG_ITEMS - ����������� �����: 1730
// DEBUG_ITEMS - ���������� �����: 1730
#define DEBUG_ITEMS

//undef L502OFF - ����������� �����: 502
//define L502OFF - ���������� �����: 502
#define L502OFF

//undef L791OFF - ����������� �����: 791
//define L791OFF - ���������� �����: 791
#define L791OFF

//define NO_EXPRESS - ����������
#define NO_EXPRESS

#ifndef DEBUG_ITEMS
#pragma message("���������� ����� 1730")
#endif

#ifndef L502OFF
#pragma message("���������� ����� 502")
#endif

#ifndef L791OFF
#pragma message("���������� ����� 791")
#endif


#define THREAD_PRIORITY

#define DISABLE_TCP

