export module sheila:registration;

namespace sheila {
export class SHEILA_API Register {
public:
  Register(const char* name, const char* tags, void (*func)(void));
};
}  // namespace sheila