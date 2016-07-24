//
// Created by dar on 4/8/16.
//

#include "ApplicationContext.h"

ApplicationContext::ApplicationContext(const std::function<bool(Window *)> &switchWindowFunc) : m_switchWindow(switchWindowFunc) { }