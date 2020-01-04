#pragma once

#include "UniformAbstract.hpp"
#include "UniformValue.hpp"

#include "Locator/Locate.hpp"
#include "History/History.hpp"

#include <imgui/imgui.h>

template <typename T>
class Uniform : public UniformAbstract {
	template <typename T>
	friend class UniformDescriptionConcrete;
public:
	Uniform(const std::string& name, HistoryType historyType, T value, T minValue = T(0), T maxValue = T(1))
		: UniformAbstract(name, historyType), m_value(value), m_valueBeforeEditingStarted(value), m_minValue(minValue), m_maxValue(maxValue) {}

	~Uniform() = default;

	void sendTo(Shader& shader, const std::string& name) override;

	bool ImGui_Slider() override;
	bool ImGui_Drag(float speed = 1.0f) override;

	UniformAbstract* createPtrWithSameData() override {
		return new Uniform<T>(getName(), m_historyType, value(), m_minValue, m_maxValue);
	}
	void setValue(T newVal, bool bPushChangeInHistory = true) {
		if (bPushChangeInHistory) {
			m_valueBeforeEditingStarted = value();
			value() = newVal;
			pushChangeInHistory();
			m_valueBeforeEditingStarted = newVal;
		}
		else
			value() = newVal;
	}

	inline const T& getValue() const { return m_value.get(); }

private:
	inline T& value() { return m_value.get(); }

	void pushChangeInHistory_IfNecessary() {
		if (ImGui::IsItemDeactivatedAfterEdit()) {
			pushChangeInHistory();
			m_valueBeforeEditingStarted = value(); // ready for next edit
		}
	}

	void pushChangeInHistory() {
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
	}

protected:
	UniformValueConcrete<T> m_value;	
	T m_valueBeforeEditingStarted;
	T m_minValue;
	T m_maxValue;
};