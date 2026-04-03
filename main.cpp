int main()
{
    AdminBase admin;
    if (!admin.authenticate())
        return 0;

    Hotel h;
    h.run();
}