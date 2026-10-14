#include "builtin.h"
#include "config.h"
#include "environment.h"
#include "gettext.h"
#include "repository.h"

int cmd_psuh(int argc, const char **argv,
            const char *prefix, struct repository *repo)
{
        int i;
        const char *cfg_name;
        const char *cfg_email;

        printf(_("Pony saying hello goes here.\n"));

        printf(Q_("Your args (there is %d):\n",
                  "Your args (there are %d):\n",
                  argc),
                argc);
        for (i = 0; i < argc; i++)
                printf("%d: %s\n", i, argv[i]);
        printf(_("Your current working directory:\n<top-level>%s%s\n"),
               prefix ? "/" : "", prefix ? prefix : "");

        repo_config(repo, git_default_config, NULL);
        if (repo_config_get_string_tmp(repo, "user.name", &cfg_name))
                printf(_("No name is foung in config\n"));
        else
                printf(_("Your name: %s\n"), cfg_name);

        if (repo_config_get_string_tmp(repo, "user.email", &cfg_email))
                printf(_("No email is foung in config\n"));
        else
                printf(_("Your email: %s\n"), cfg_email);
        return 0;
}
