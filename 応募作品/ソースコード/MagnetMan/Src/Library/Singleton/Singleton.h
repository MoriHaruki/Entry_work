#pragma once

#include "Common.h"

/*
	シングルトン管理クラス
	シングルトンを採用するときはこのヘッダーをインクルードすること	
*/

namespace MyLib {
	template<class T>
	class Singleton {
		// コンストラクタ、デストラクタは外部生成禁止
	protected:
		Singleton(){}
		virtual ~Singleton() {}

	public:
		// インスタンスが生成されていなければNEWで生成する
		inline static T* Get() { return (!instance_) ? instance_ = NEW T : instance_; }
		// インスタンス削除
		inline static void Delete() { if (instance_) { delete instance_; instance_ = nullptr; } }

	private:
		// インスタンス
		inline static T* instance_ = nullptr;
	};
}
