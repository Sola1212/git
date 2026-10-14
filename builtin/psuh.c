#include "builtin.h"
#include "commit.h"
#include "config.h"
#include "environment.h"
#include "gettext.h"
#include "pretty.h"
#include "repository.h"
#include "strbuf.h"
#include "wt-status.h"

int cmd_psuh(int argc, const char **argv,
            const char *prefix, struct repository *repo)
{
        int i;
        const char *cfg_name;
        const char *cfg_email;
        struct wt_status status;
        struct commit *c = NULL;
        struct strbuf commitline = STRBUF_INIT;

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

        wt_status_prepare(repo, &status);
        repo_config(repo, git_default_config, &status);

        printf(_("Your current branch: %s\n"), status.branch);
        printf(_("Index File: %s\n"), status.index_file);

        c = lookup_commit_reference_by_name("origin/master");

        if (c != NULL) {
            pp_commit_easy(CMIT_FMT_ONELINE, c, &commitline);
            printf(_("Current commit: %s\n"), commitline.buf);
        }

        return 0;
}
