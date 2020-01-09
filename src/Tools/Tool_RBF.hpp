#pragma once

#include "Tool_Shape.hpp"

#include "RBF/Function.hpp"
#include "RBF/Function_Gaussian.hpp"
#include "RBF/Function_Inverse.hpp"
#include "RBF/Function_QuasiIdentityMinOne.hpp"
#include "RBF/Function_Identity.hpp"

#include <glm/glm.hpp>
#include <Eigen/Dense>

#include <vector>

class Tool_RBF : public Tool_Shape {
public:
	Tool_RBF();
	~Tool_RBF() = default;

	void onLeftClicDown(const Cursor& cursor) override;
	void update(const Cursor& cursor) override;

protected:
	void applyOnShape(std::function<void(const glm::ivec3& pos)> whatToDoWithPos) override;

	virtual void reset();

	virtual void addAnchorPoint(const glm::ivec3& pos) = 0;
	virtual void evaluateRBFOnWorld(std::function<void(const glm::ivec3 & pos)> whatToDoWithPos) = 0;
	virtual void ImGui_Window() = 0;

	bool ImGui_ModulingFunction();
	bool ImGui_Condition();
	void ImGui_Finalize(bool bComputePreview);

protected:
	Eigen::VectorXf m_valuesAtAnchorPts;

	bool m_bInvertSelection;

	float m_threshhold;
	bool m_bSurfaceMode;
	int m_modulingFunctionID;

	static Function* m_modulingFunction;
	static Function_Gaussian m_gaussian;
	static Function_Inverse m_inverse;
	static Function_QuasiIdentityMinOne m_quasiIdentity;
	static Function_Identity m_identity;
};

