

# File glob.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**utils**](dir_313caf1132e152dd9b58bea13a4052ca.md) **>** [**glob.h**](glob_8h.md)

[Go to the documentation of this file](glob_8h.md)


```C++
#ifndef GLOB_H
#define GLOB_H

#include <memory>
#include <string>

namespace glob {

    class glob_impl;

    class glob final
    {
    public:
        glob(const std::string &pattern);
        ~glob();

        operator bool() const {
            return is_valid();
        }

        void open(const std::string &pattern);
        void close();

        std::string dir_path;
        std::string current_match() const;

        bool next();
        bool is_valid() const;

    private:
        glob(const glob &) = delete;
        void operator=(const glob &) = delete;

    private:
        std::unique_ptr<glob_impl> impl_;
    };

} // namespace glob

#endif // !GLOB_H
```


