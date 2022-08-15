#include "IInput.h"

std::shared_ptr<IInput> IInput::defaultInput_ = std::make_shared<NullInput>();

void IInput::EvaluateKey(KeyInput::Key key, KeyInput::Action action, int mods)
{
	if (!headContext)
	{
		LOG_COLOR("Did not registed any Context.", COLOR::YELLOW, COLOR::BLACK);
		return;
	}
	std::string actionName = headContext->MapKeyAction(key, mods);
	std::pair<std::string, float> rangePack = headContext->MapKeyRange(key, mods);

	if (!(actionName == "")) {
//		std::cout << "Calling Action: " << actionName << std::endl;
		auto it = actionMap.find(actionName);
		if (it != actionMap.end())
			it->second(action);
	}
	
	if (!(rangePack.first == "")) {
		std::cout << "Calling Range: " << rangePack.first << "Mod" << mods << std::endl;
		auto it = rangeMap.find(rangePack.first);
		if (it != rangeMap.end())
		{
			it->second.first(action, rangePack.second);
			std::cout << it->second.second << std::endl;
		}
	}
}



void IInput::BindAction(const std::string& name, ActionCallback func)
{
	auto it = actionMap.find(name);
	if (it != actionMap.end()) {
		std::cout << "WARNING! Overwriting alias for action function" << std::endl;
	};
	actionMap[name] = func;
}

void IInput::BindRange(const std::string& name, RangeCallback func, float weight)
{
	auto it = rangeMap.find(name);
	if (it != rangeMap.end()) {
		std::cout << "WARNING! Overwriting alias for range function" << std::endl;
	};
	rangeMap[name] = { func, weight };
	std::cout << "name" << name << weight << std::endl;
}

void IInput::AddContext(Context* con)
{
	AddContext(std::shared_ptr<Context>(con));
}

void IInput::AddContext(std::shared_ptr<Context> con)
{
	if (headContext) {
		auto cur = headContext;
		while (cur->next_) {
			cur = cur->next_;
		}
		cur->next_ = con;
		con->ResetPriority(cur->priority_ + 1);
	}
	else {
		headContext = con;
	}
}

void IInput::RemoveContext(Context* con)
{
	RemoveContext(std::shared_ptr<Context>(con));
}

void IInput::RemoveContext(std::shared_ptr<Context> con)
{
	auto cur = headContext;
	if (cur) {
			while (cur->next_) {
				if (cur->next_ == con) {
					cur->next_ = cur->next_->next_;
					break;
				}
				cur = cur->next_;
			}
			if(headContext == con)
				headContext.reset();
	}
}

void IInput::ActivateContext(Context* con)
{
	ActivateContext(std::shared_ptr<Context> (con));
}

void IInput::ActivateContext(std::shared_ptr<Context> con)
{
	con->Activate();
}

void IInput::DeactivateContext(Context* con)
{
	DeactivateContext(std::shared_ptr<Context>(con));
}

void IInput::DeactivateContext(std::shared_ptr<Context> con)
{
	con->Deactivate();
}
void IInput::ResetPriority(Context* con, int priorityLevel) {
	ResetPriority(std::shared_ptr<Context>(con), priorityLevel);
}

void IInput::ResetPriority(std::shared_ptr<Context> con, int priorityLevel)
{	
	auto cur = headContext;
	std::shared_ptr<Context> target;
	std::shared_ptr<Context> nextLargerContext;
	if (cur) {
		while (cur->next_ && (!target && !nextLargerContext)) {
			if (cur->priority_ <= priorityLevel) {
				nextLargerContext = cur;
			}
			if (cur->next_ == con) {
				target = cur->next_;
				cur->next_ = cur->next_->next_;
			}
			cur = cur->next_;
		}
		if(target){
			target->next_ = nextLargerContext->next_;
			nextLargerContext->next_ = target;
		}
	}
}