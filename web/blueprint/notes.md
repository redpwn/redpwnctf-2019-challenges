It's important that people can download the source as an archive, rather than just individual files. This problem relies on a now-patched prototype injection bug in a specific version of lodash, so people should be able to inspect the package.json to see what version of lodash is being used.

also: the blueprint.js which should be deployed is slightly different from the blueprint.js in the blueprint.tar.gz. It contains checks to make sure the prototype injection only affects the current user
