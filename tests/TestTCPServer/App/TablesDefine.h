#pragma once

#define DEFINE_PARAM(z, type, def_val) struct z\
{\
	typedef type type_value;\
	type_value value;\
	const type_value default_value;\
	const wchar_t *name(){return L#z;}\
	z() : value(def_val), default_value(def_val) {}\
};

template<class T>struct ID
{
	typedef typename T::__template_must_be_overridded__ noused;
};

#define DEFINE_PARAM_ID(z, type, def_val) template<> struct ID<z>\
{\
	typedef type type_value;\
	type_value value;\
	const type_value default_value;\
	const wchar_t *name(){return L#z##L"ID";}\
	ID() : value(def_val), default_value(def_val) {}\
};

#define DEFINE_PARAM_WAPPER_ID(W, z, type, def_val) template<> struct ID<W<z> >\
{\
	typedef type type_value;\
	type_value value;\
	const type_value default_value;\
	const wchar_t *name(){return L#W##L#z##L"ID";}\
	ID() : value(def_val), default_value(def_val) {}\
};

#define DEFINE_PARAM_NUM(z, n, type, def_val) template<>struct z<n>\
{\
	typedef type type_value;\
	type_value value;\
	const type_value default_value;\
	const wchar_t *name(){return L###z##L###n;}\
	z() : value(def_val), default_value(def_val) {}\
};

#define STR_PARAM(namePar, len, txt)struct namePar\
{\
	typedef Holder<len> type_value;\
	type_value value;\
	type_value default_value;\
	const wchar_t *name(){return L###namePar;}\
	namePar()\
	{\
		default_value = txt;\
		value = default_value;\
	}\
};

#define CHAR_PARAM(namePar, len, txt)struct namePar\
{\
	typedef CharHolder<len> type_value;\
	type_value value;\
	type_value default_value;\
	const wchar_t *name(){return L###namePar;}\
	namePar()\
    {\
	   default_value = txt;\
	   value = default_value;\
    }\
};

#define DEFINE_PARAM_WAPPER(wapper, z, type, def_val) template<> struct wapper<z>\
{\
	typedef type type_value;\
	type_value value;\
	const type_value default_value;\
	const wchar_t *name(){return L#wapper##L#z;}\
	wapper() : value(def_val), default_value(def_val) {}\
};

#define DEFINE_PARAM_WAPPER_NUM(wapper, z, n, type, def_val) template<> struct wapper<z, n>\
{\
	typedef type type_value;\
	type_value value;\
	const type_value default_value;\
	const wchar_t *name(){return L#wapper##L#z##L#n;}\
	wapper() : value(def_val), default_value(def_val) {}\
};

#define DEFINE_PARAM_WAPPER_2_NUM(W, wapper, z, n, type, def_val) template<> struct W<wapper<z, n> >\
{\
	typedef type type_value;\
	type_value value;\
	const type_value default_value;\
	const wchar_t *name(){return L#W##L#wapper##L#z##L#n;}\
	W() : value(def_val), default_value(def_val) {}\
};

#define DEFINE_ARRAY_PARAM_WAPPER(wapper, z, type, count, def_val) template<>struct wapper<z>\
{\
	typedef type type_value[count];\
	type_value value;\
	const type default_value;\
	const wchar_t *name(){return L#wapper##L#z;}\
	wapper(): default_value(def_val) \
    {\
		for(int i = 0; i < count; ++i) value[i] = def_val;\
	}\
};

#define DEFINE_WAPPER(Name, type, def_val)template<>struct Name	 \
{\
	typedef GetItemsList<Name>::Result items_list;\
	typedef type type_value;\
	type_value value;\
	const type_value default_value;\
	Name() : value(def_val), default_value(def_val)\
    {\
	 TrimTypeList(Buf(),L#Name);\
    }\
	static wchar_t *Buf(){static wchar_t buf[dimention_of(L#Name)]; return buf;};\
	wchar_t *name(){return Buf();}\
};



