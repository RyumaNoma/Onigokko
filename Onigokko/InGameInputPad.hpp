﻿#pragma once
#include "InGameInputInterface.hpp"
#include "DxLib.h"

namespace game {
    /**
     * @brief XInputのみに対応。
     */
    class InGameInputPad :
        public InGameInputInterface
    {
    public:
        /**
         * @brief コンストラクタ。
         * 
         * @param id パッドId
         */
        InGameInputPad(int id);

        /**
         * @brief 左スティックで8方向入力。
         * 
         * @return  移動方向
         */
        virtual MOVE_DIRECTION move() override;

        /**
         * @brief 左スティックの方向。
         * 
         * @return  方向
         */
        virtual Direction getDirection() override;

        /**
         * @brief Bボタンでスキルアイテム取得。
         * 
         * @return  スキルアイテム取得するならtrue
         */
        virtual bool getSkillItem() override;

        /**
         * @brief Aボタンでスキルアイテム使用。
         * 
         * @return  使用しようとするならtrue
         */
        virtual bool useSkillItem() override;

        /**
         * @brief パッドIdの取得。
         * 
         * @return  Id
         */
        int getId() const { return _id; }

        /**
         * @brief ジョイパッドの方向入力の無効範囲を設定する。
         * 
         * @param zone 無効範囲(0.0～1.0)
         */
        void setDeadZone(double zone);
    private:
        XINPUT_STATE getInputState() const;
        int _id;
    };
    using InGameInputPadPtr = std::shared_ptr<InGameInputPad>;
    using InGameInputPadRef = std::shared_ptr<const InGameInputPad>;
}
