#pragma once
#include "MessageClient.hpp"
#include "DxLib.h"

namespace game {
    /**
     * @brief XInputのみに対応。
     */
    class InGameInputPad :
        public MessageClient
    {
    public:

        /**
         * @brief コンストラクタ。
         * 
         * @param padId パッドId
         */
        InGameInputPad(int padId, MessageServerPtr server);

        virtual void receive(const std::string& message) override;

        /**
         * @brief パッドIdの取得。
         * 
         * @return  Id
         */
        int getPadId() const { return _id; }

        /**
         * @brief ジョイパッドの方向入力の無効範囲を設定する。
         * 
         * @param zone 無効範囲(0.0～1.0)
         */
        void setDeadZone(double zone);
    private:
        XINPUT_STATE getInputState() const;

        void responseMove() const;
        void responseGetSkillItem() const;
        void responseUseSkillItem() const;
    private:
        int _padId;
    };
    using InGameInputPadPtr = std::shared_ptr<InGameInputPad>;
    using InGameInputPadRef = std::shared_ptr<const InGameInputPad>;
}
