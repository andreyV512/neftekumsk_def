#pragma once
#include "AppBase.h"
//-----------------------------------------------------------------
template<class O>struct __status_label__
{
	typedef typename O::__template_must_be_overridded__ noused;
};

template<>struct __status_label__<NullType>
{
	static const int ID = 0;
	static char *text(){return "NO_MESSAGE";}
};

#define STATUS_LABEL(O, txt)template<>struct __status_label__<O>\
{\
	static const int ID = TL::IndexOf<ColorTable::items_list, O>::value;\
	static char *text(){return txt;};\
};

namespace
{
	struct __data_text__
	{
		int id;
		char *text;
		int color;
		bool visibleVal;
	};
	template<class T>struct ValueVisible
	{
		static const bool value = true;
	};
	template<>struct ValueVisible<Clr<Undefined>>
	{
		static const bool value = false;
	};
	template<>struct ValueVisible<Clr<DeathZone>>
	{
		static const bool value = false;
	};
	template<class O, class P>struct __select__
	{
		bool operator()(O *o, P *p)
		{
			if(TL::IndexOf<ColorTable::items_list, O>::value == p->id)
			{
				p->text = __status_label__<O>::text();
				p->color = o->value;
				p->visibleVal = ValueVisible<O>::value;
				return false;
			}
			return true;
		}
	};
}

STATUS_LABEL(Clr<Undefined>, "\"Результат не определён\"")
STATUS_LABEL(Clr<DeathZone>, "\"Мёртвая зона\"")

STATUS_LABEL(Clr<Nominal>, "\"1 класс\"")

STATUS_LABEL(Clr<BKlass2<Thickness>>, "толщина \"2 класс\"") 
STATUS_LABEL(Clr<BKlass3<Thickness>>, "толщина \"3 класс\"") 
STATUS_LABEL(Clr<BDefect<Thickness>>, "толщина \"брак\"")
//---------------------------------------------------------------------------
template<class O, class P>struct __set_color_bar__;

namespace
{
	struct __data_color__
	{
		int id;
		unsigned &color;
		double &data;
		double defData;
		__data_color__(int id, unsigned &color, double &data, double defData)
			: id(id)
		    , color(color)
		    , data(data)
			, defData(defData)
		{}
	};
}

template<class T>struct __clr__;
template<class _0, class _1, class _2, class _3>struct __clr__<Clr<_0,_1,_2,_3>>
{
	typedef Clr<_0> Result;
};

template<class O, class P>struct __set_color_bar__
{
	int &color;
	__set_color_bar__() 
		: color(Singleton<ColorTable>::Instance().items.get<O>().value)
	{}
	bool operator()(O *, P *p)
    {
        if(TL::IndexOf<ColorTable::items_list, O>::value == p->id)
		{
		     p->color = color;
             return false;
		}
		return true;
    }
};

#define COLOR_DATA(O)template<class P>struct __set_color_bar__<O, P>\
{\
	int &color;\
	__set_color_bar__() \
        : color(Singleton<ColorTable>::Instance().items.get<O>().value)\
        {}\
	bool operator()(O *, P *p)\
    {\
        if(TL::IndexOf<ColorTable::items_list, O>::value == p->id)\
		{\
		     p->color = color;\
			 p->data = p->defData;\
             return false;\
		}\
		return true;\
    }\
};

COLOR_DATA(Clr<Undefined>)
COLOR_DATA(Clr<DeathZone>)

#define TXT(a, b) a##_##b
#define STR(a, b) a<b>
#define PARAM_STR(a, b) STR(a, b)
#define PARAM_TXT(a, b) TXT(a, b)

#define STATUS_LABEL_1(a)template<>struct __status_label__<Clr<PARAM_STR##a>>\
{\
	static const int ID = TL::IndexOf<ColorTable::items_list, Clr<PARAM_STR##a>>::value;\
	static char *text(){return PARAM_TXT##a;}\
};

#define STATUS_LABEL_2(a, b)template<>struct __status_label__<Clr<PARAM_STR##a, PARAM_STR##b>>\
{\
	static const int ID = TL::IndexOf<ColorTable::items_list, Clr<PARAM_STR##a, PARAM_STR##b>>::value;\
	static char *text(){return PARAM_TXT##a##PARAM_TXT##b;}\
};

#define STATUS_LABEL_3(a, b, c)template<>struct __status_label__<Clr<PARAM_STR##a, PARAM_STR##b, PARAM_STR##c>>\
{\
	static const int ID = TL::IndexOf<ColorTable::items_list, Clr<PARAM_STR##a, PARAM_STR##b, PARAM_STR##c>>::value;\
	static char *text(){return PARAM_TXT##a##PARAM_TXT##b##PARAM_TXT##c;};\
};

#define STATUS_LABEL_4(a, b, c, d)template<>struct __status_label__<Clr<PARAM_STR##a, PARAM_STR##b, PARAM_STR##c, PARAM_STR##d>>\
{\
	static const int ID = TL::IndexOf<ColorTable::items_list, Clr<PARAM_STR##a, PARAM_STR##b, PARAM_STR##c, PARAM_STR##d>>::value;\
	static char *text(){return PARAM_TXT##a##PARAM_TXT##b##PARAM_TXT##c##PARAM_TXT##d;}\
};

#define BDefect_Cross "\"поперечный дефект\", "
#define BDefect_Long "\"продольный дефект\", "

#define BKlass2_Cross "\"поперечный 2 класс\", "
#define BKlass2_Long "\"продольный 2 класс\", "

#define BDefect_Thickness "\"толщина 1 класс\", "
#define BKlass2_Thickness "\"толщина 2 класс\", "
#define BKlass3_Thickness "\"толщина 3 класс\", "

STATUS_LABEL_1((BDefect, Cross))
STATUS_LABEL_1((BDefect, Long))

STATUS_LABEL_1((BKlass2, Cross))
STATUS_LABEL_1((BKlass2, Long))

//STATUS_LABEL_1((BKlass3, Thickness))

//STATUS_LABEL_2((BDefect, Thickness), (BKlass2, Thickness))

STATUS_LABEL_2((BDefect, Cross), (BKlass2, Thickness))
STATUS_LABEL_2((BDefect, Cross), (BDefect, Thickness))
//STATUS_LABEL_3((BDefect, Cross), (BDefect, Thickness), (BKlass2, Thickness))

STATUS_LABEL_2((BDefect, Long), (BKlass2, Thickness))
STATUS_LABEL_2((BDefect, Long), (BDefect, Thickness))
//STATUS_LABEL_3((BDefect, Long), (BDefect, Thickness), (BKlass2, Thickness))

STATUS_LABEL_2((BDefect, Cross), (BDefect, Long))

STATUS_LABEL_3((BDefect, Cross), (BDefect, Long), (BKlass2, Thickness))
STATUS_LABEL_3((BDefect, Cross), (BDefect, Long), (BDefect, Thickness))
//STATUS_LABEL_4((BDefect, Cross), (BDefect, Long), (BDefect, Thickness), (BKlass2, Thickness))
//----------------------------------------------------------------------
STATUS_LABEL_2((BKlass2, Cross), (BKlass2, Thickness))
STATUS_LABEL_2((BDefect, Thickness), (BKlass2, Cross))
				
STATUS_LABEL_2((BKlass2, Long), (BKlass2, Thickness))
STATUS_LABEL_2((BDefect, Thickness), (BKlass2, Long))
			
STATUS_LABEL_2((BKlass2, Cross), (BKlass2, Long))
				
STATUS_LABEL_3((BKlass2, Cross), (BKlass2, Long), (BKlass2, Thickness))
STATUS_LABEL_3((BDefect, Thickness), (BKlass2, Cross), (BKlass2, Long))
//---------------
STATUS_LABEL_2((BDefect, Cross), (BKlass2, Long))
				
STATUS_LABEL_3((BDefect, Cross), (BKlass2, Long), (BKlass2, Thickness))
STATUS_LABEL_3((BDefect, Cross), (BKlass2, Long), (BDefect, Thickness))
//----------------------------------
STATUS_LABEL_2((BDefect, Long), (BKlass2, Cross))
								
STATUS_LABEL_3((BDefect, Long), (BKlass2, Cross), (BKlass2, Thickness))
STATUS_LABEL_3((BDefect, Long), (BKlass2, Cross), (BDefect, Thickness))


STATUS_LABEL_2((BDefect, Cross), (BKlass3, Thickness))
STATUS_LABEL_2((BDefect, Long), (BKlass3, Thickness))


#undef COLOR_DATA
#undef STATUS_LABEL
#undef STATUS_LABEL_2
#undef STATUS_LABEL_3
#undef STATUS_LABEL_4
#undef TXT
#undef STR
#undef PARAM_STR
#undef PARAM_TXT

#undef BDefect_Cross
#undef BDefect_Long 
#undef BKlass2_Cross 
#undef BKlass2_Long 
#undef BDefect_Thickness
#undef BKlass2_Thickness
//------------------------------------------------------------------------------------------------
struct StatusText
{
	char *operator()(int id, int &color, bool &visible)
	{
		__data_text__ data = {id, NULL};
		TL::find<ColorTable::items_list, __select__>()(		
			&Singleton<ColorTable>::Instance().items
			, &data
			);
		color = data.color;
		visible = data.visibleVal;
		return data.text;
	}
};

struct ColorBar
{
	void operator()(double &data, unsigned &color, int id, double defData)
	{
		__data_color__ d(id, color, data, defData);
		TL::find<ColorTable::items_list, __set_color_bar__>()((TL::Factory<ColorTable::items_list> *)0, &d);
	}
};
