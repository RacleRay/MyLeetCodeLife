#ifndef CSP_H
#define CSP_H

#include <algorithm>
#include <cassert>
#include <iterator>
#include <map>
#include <vector>

template <typename C>
using Constraints = std::vector<C>;

template <typename V, typename D>
using Domains = std::map<V, std::vector<D>>;

template <typename V>
using Variables = std::vector<V>;

template <typename V, typename D>
using Assignment = std::map<V, D>;

/**
 * @brief 两个变量赋值是否冲突的条件约束
 *
 * @tparam V
 * @tparam D
 */
template <typename V, typename D>
struct BinaryConstraint
{
    V var1;
    V var2;
    bool contains(const V &var) const
    {
        return var1 == var || var2 == var;
    }
    bool is_satisfied(const Assignment<V, D> &assign) const
    {
        const auto vp1 = assign.find(var1);
        const auto vp2 = assign.find(var2);
        const auto endp = assign.cend();
        return (vp1 == endp || vp2 == endp) || vp1->second != vp2->second;
    }
};

template <typename C, typename D, typename V>
bool is_consistent(const V &var, const Assignment<V, D> &assignment, const Constraints<C> &constraints)
{
    for (auto const &c : constraints)
    {
        if (!c.contains(var))
            continue;
        if (!c.is_satisfied(assignment))
            return false;
    }
    return true;
}

template <typename V, typename D>
const V &next_variable(const Variables<V> &variables, const Assignment<V, D> &assigment)
{
    const auto it = std::find_if(variables.cbegin(), variables.cend(),
                                 [&assigment](const V &v)
                                 { return assigment.find(v) == assigment.end(); });
    assert(it != variables.cend());
    return *it;
}

template <typename C, typename D, typename V>
Assignment<V, D> backtracking_search(
    const Constraints<C> &constraints,
    const Domains<V, D> &domains,
    const Variables<V> &variables,
    const Assignment<V, D> &assignment)
{
    if (assignment.size() == variables.size())
        return assignment;
    const auto &variable = next_variable(variables, assignment);
    for (const auto &value : domains.at(variable))
    {
        auto local_assignment = assignment;
        local_assignment[variable] = value;
        if (is_consistent<C, D, V>(variable, local_assignment, constraints))
        {
            const auto ans = backtracking_search(constraints, domains, variables, local_assignment);
            if (!ans.empty())
                return ans;
        }
    }
    return {};
}

template <typename C, typename D, typename V>
Assignment<V, D> backtracking_search(
    const Constraints<C> &constraints,
    const Domains<V, D> &domains,
    const Variables<V> &variables)
{
    return backtracking_search(constraints, domains, variables, {});
}

#endif // Basic part.
