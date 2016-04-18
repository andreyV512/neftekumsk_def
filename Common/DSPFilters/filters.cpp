#include "filters.h"
#include "Include/Dsp.h"

//! @brief Тип для функции фильтрации по Чебышеву
//! @param data - массив с сигналом
//! @param N - размер массива
//! @param order - порядок фильтра
//! @param sampleRate - частота сбора
//! @param cutoffFrequency - частота среза
//! @param centerFrequency частота центра фильтра
//! @param widthFrequency ширина фильтра
//! @param rippleDb пульсации в полосе пропускания
//! @param type - тип фильтра 0 - LowPass,1 - HighPass,2 - BandPass,3 - BandStop
void ChebyshevI::Do(double *data,int N,
                                       int order,
                                       double sampleRate,
                                       double cutoffFrequency,
                                       double centerFrequency,
                                       double widthFrequency,
                                       double rippleDb,
                                       int type)
{
    switch(type)
    {
        case 0:
        {
            Dsp::SimpleFilter<Dsp::ChebyshevI::LowPass<20>,1> filter;
            filter.setup(order,                 //Порядок
                         sampleRate,            //Частота дискретизации
                         cutoffFrequency,       //Частота среза
                         rippleDb);             //Пульсации
            filter.process(N,&data);
            break;
        }
        case 1:
        {
            Dsp::SimpleFilter<Dsp::ChebyshevI::HighPass<20>,1> filter;
            filter.setup(order,                 //Порядок
                         sampleRate,            //Частота дискретизации
                         cutoffFrequency,       //Частота среза
                         rippleDb);             //Пульсации
            filter.process(N,&data);
            break;

        }
        case 2:
        {
            Dsp::SimpleFilter<Dsp::ChebyshevI::BandPass<20>,1> filter;
            filter.setup(order,                 //Порядок
                         sampleRate,            //Частота сбора
                         centerFrequency,       //Частота центра фильтрации
                         widthFrequency,        //Ширина фильтра
                         rippleDb);             //Пульсации
            filter.process(N,&data);
            break;
        }
        case 3:
        {
            Dsp::SimpleFilter<Dsp::ChebyshevI::BandStop<20>,1> filter;
            filter.setup(order,                 //Порядок
                         sampleRate,            //Частота сбора
                         centerFrequency,       //Частота центра фильтрации
                         widthFrequency,        //Ширина фильтра
                         rippleDb);             //Пульсации
            filter.process(N,&data);
            break;
        }
    }
}

//! @brief Тип для функции фильтрации по Баттерворту
//! @param data - массив с сигналом
//! @param N - размер массива
//! @param order - порядок фильтра
//! @param sampleRate - Частота сбора
//! @param cutoffFrequency - частота среза
//! @param centerFrequency - частота центра фильтра
//! @param widthFrequency - ширина фильтра
//! @param type - тип фильтра 0 - LowPass,1 - HighPass,2 - BandPass,3 - BandStop
void Butterworth::Do(double *data,int N,
                                     int order,
                                     double sampleRate,
                                     double cutoffFrequency,
                                     double centerFrequency,
                                     double widthFrequency,
                                     int type)
{
    switch(type)
    {

        case 0:
        {
            Dsp::SimpleFilter <Dsp::Butterworth::LowPass<20>,1> filter;
            filter.setup(order,             //Порядок
                         sampleRate,        //Частота сбора
                         cutoffFrequency);  //частота среза

            filter.process(N,&data);
        }
        case 1:
        {
            Dsp::SimpleFilter <Dsp::Butterworth::HighPass<20>,1> filter;
            filter.setup(order,             //Порядок
                         sampleRate,        //Частота сбора
                         cutoffFrequency);  //частота среза

            filter.process(N,&data);
        }
        case 2:
        {
            Dsp::SimpleFilter <Dsp::Butterworth::BandPass<20>,1> filter;
            filter.setup(order,             //Порядок
                         sampleRate,        //Частота сбора
                         centerFrequency,   //Частота центра
                         widthFrequency);   //Ширина фильтра

            filter.process(N,&data);
        }

        case 3:
        {
            Dsp::SimpleFilter <Dsp::Butterworth::BandStop<20>,1> filter;
            filter.setup(order,             //Порядок
                         sampleRate,        //Частота сбора
                         centerFrequency,   //Частота центра
                         widthFrequency);   //Ширина фильтра

            filter.process(N,&data);
        }

    }
}
//! @brief Тип для функции фильтрации по Баттерворту
//! @param data - массив с сигналом
//! @param N - размер массива
//! @param order - порядок фильтра
//! @param sampleRate - Частота сбора
//! @param cutoffFrequency - частота среза
//! @param centerFrequency - Частота центра фильтра
//! @param widthFrequency - ширина фильтра
//! @param rippleDb - Пульсации в полосе пропускания
//! @param rolloff - пульсации в полосе подавления
//! @param type - тип фильтра 0 - LowPass,1 - HighPass,2 - BandPass,3 - BandStop
void Elliptic::Do(double *data,int N,
                                              int order,
                                              double sampleRate,
                                              double cutoffFrequency,
                                              double centerFrequency,
                                              double widthFrequency,
                                              double rippleDb,
                                              double rolloff,
                                              int type)
{
    switch(type)
    {
        case 0:
        {
            Dsp::SimpleFilter < Dsp::Elliptic::LowPass<20>,1> filter;
            filter.setup(order,             //Порядок
                         sampleRate,        //Частота сбора
                         cutoffFrequency,   //частота среза
                         rippleDb,          //пульсации в полосе пропускания
                         rolloff);          //пульсации в полосе подавления
            filter.process(N,&data);
            break;
        }

        case 1:
        {
            Dsp::SimpleFilter < Dsp::Elliptic::HighPass<20>,1> filter;
            filter.setup(order,             //Порядок
                         sampleRate,        //Частота сбора
                         cutoffFrequency,   //частота среза
                         rippleDb,          //пульсации в полосе пропускания
                         rolloff);          //пульсации в полосе подавления
            filter.process(N,&data);
            break;
        }

        case 2:
        {
            Dsp::SimpleFilter < Dsp::Elliptic::BandPass<20>,1> filter;
            filter.setup(order,             //Порядок
                         sampleRate,        //Частота сбора
                         centerFrequency,   //Частота центра
                         widthFrequency,    //Ширина фильтра
                         rippleDb,          //Пульсации в полосе пропускания
                         rolloff);          //Пульсации в полосе подавления

            filter.process(N,&data);
            break;
        }
        case 3:
        {
            Dsp::SimpleFilter < Dsp::Elliptic::BandStop<20>,1> filter;
            filter.setup(order,             //Порядок
                         sampleRate,        //Частота сбора
                         centerFrequency,   //Частота центра
                         widthFrequency,    //Ширина фильтра
                         rippleDb,          //Пульсации в полосе пропускания
                         rolloff);          //Пульсации в полосе подавления

            filter.process(N,&data);
            break;
        }
    }
}
