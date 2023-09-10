#pragma once
#include "DxLib.h"
#include <string>

/**
 * @brief モデルファイルのデータを読み込む。
 * 
 * @details テクスチャ貼り付け機能なし
 * @details 画像の透明度は無効で固定
 */
class ModelResource {
public:
	/**
	 * @brief デフォルトコンストラクタ。全て空で初期化される
	 */
	ModelResource();

	/**
	 * @brief コンストラクタ。モデル用ファイルによって初期化を行う。
	 * 
	 * @param filepath モデル用ファイル
	 */
	ModelResource(std::string filepath);

	/**
	 * @brief デストラクタ。
	 */
	~ModelResource();

	/**
	 * @brief 既に設定されたファイルからのリロード。
	 * @brief ホットリロードに使われることを想定している。
	 * @throw std::runtime_error("could not open file") 何らかの理由でファイルを開けなかった場合
	 */
	void reload();

	/**
	 * @brief モデル用ファイルのパスを設定する。
	 * 
	 * @param filepath モデル用ファイル
	 */
	void setFilepath(const std::string& filepath);

	/**
	 * @brief 頂点バッファの取得。
	 * 
	 * @return  頂点バッファの先頭アドレス
	 */
	VERTEX3D* getVertexBuffer() const { return _vertexBuffer; }

	/**
	 * @brief 頂点数の取得。
	 * 
	 * @return  頂点数
	 */
	int getVertexNum() const { return _vertexNum; }

	/**
	 * @brief インデックスバッファの取得。
	 * 
	 * @return  インデックスバッファの先頭アドレス
	 */
	unsigned short* getIndexBuffer() const { return _indexBuffer; }

	/**
	 * @brief ポリゴン数の取得。
	 * 
	 * @return  ポリゴン数
	 */
	int getPolygonNum() const { return _polygonNum; }
private:
	void destroy();
	void load();
private:
	std::string _filepath;
	VERTEX3D* _vertexBuffer;
	int _vertexNum;
	unsigned short* _indexBuffer;
	int _polygonNum;
};
