import time

class GPIOMock:
    def __init__(self, pin_number):
        self.pin_number = pin_number
        self._value = 0
        self._start_time = None
        self._hist = []

    @property
    def value(self):
        return self._value
    
    @value.setter
    def value(self, val):
        if self._start_time is None:
            self._start_time = time.time()
        t = time.time() - self._start_time
        self._hist.append((t, val))
        self._value = val

    def get_history(self):
        return list(self._hist)

    @value.setter
    def export(self, val):
        if not val and self._start_time is not None:
            t = time.time() - self._start_time
            self._hist.append((t, self._value))
