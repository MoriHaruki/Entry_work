#pragma once

enum class FieldID
{
	Field01,
	Field02,

	NUM,
};

#define IFIELD_ID (int)FieldID

struct FieldParameter
{
	const char	*file_path;	//フィールドのモデルファイルパス
};

static const FieldParameter FIELD_DATA_BASE[IFIELD_ID::NUM] = {

	//STAGE01
	{"Data/Model/Field/1Field.x"},

	//STAGE02
	{"Data/Model/Field/2Field.x"},
};
