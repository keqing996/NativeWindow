from abc import ABC, abstractmethod

class ToolChain(ABC):

    @abstractmethod
    def valid(self) -> bool:
        return False

    @abstractmethod
    def get_c_compiler(self) -> str:
        return ''

    @abstractmethod
    def get_cpp_compiler(self) -> str:
        return ''


class ToolChainMsvc:
    pass

class ToolChainClang:
    pass

class ToolChainMingw:
    pass