#pragma once

#include "Uniform.hpp"
#include "UniformValue.hpp"

#include "Locator/Locate.hpp"
#include "History/History.hpp"

#include <imgui/imgui.h>

template <typename T>
class UniformConcrete : public Uniform {
	template <typename T>
	friend class UniformDescriptionConcrete;
public:
	UniformConcrete(const std::string& name, HistoryType historyType, T value, T minValue, T maxValue)
		: Uniform(name, historyType), m_value(value), m_valueBeforeEditingStarted(value), m_minValue(minValue), m_maxValue(maxValue) {}

	~UniformConcrete() = default;

	void sendTo(Shader& shader, const std::string& name) override;

	void ImGui_Slider() override;

	Uniform* createPtrWithSameData() override {
		return new UniformConcrete<T>(getName(), m_historyType, value(), m_minValue, m_maxValue);
	}

	inline T& value() { return m_value.get(); }

private:
	void pushChangeInHistory_IfNecessary() {
		if (ImGui::IsItemDeactivatedAfterEdit()) {
			History& history = Locate::history(m_historyType);
			history.beginUndoGroup();
			T val = value();
			T prevVal = m_valueBeforeEditingStarted;
			history.addAction(Action(
				// DO action
				[this, val]()
			{
				this->m_value = val;
			},
				// UNDO action
				[this, prevVal]()
			{
				this->m_value = prevVal;
			}
			));
			history.endUndoGroup();
			m_valueBeforeEditingStarted = value(); // ready for next edit
		}
	}

protected:
	UniformValueConcrete<T> m_value;	
	T m_valueBeforeEditingStarted;
	T m_minValue;
	T m_maxValue;
};